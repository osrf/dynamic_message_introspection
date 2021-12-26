// Copyright 2020 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "dynmsg/message_reading.hpp"
#include "dynmsg/msg_parser.hpp"
#include "dynmsg_demo/cli.hpp"
#include "dynmsg_demo/typesupport_utils.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <thread>

#include "rcl/context.h"
#include "rcl/error_handling.h"
#include "rcl/graph.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/rcl.h"
#include "rcl/subscription.h"
#include "rcl/types.h"
#include "rcl_action/graph.h"

#include "rcutils/logging_macros.h"


#include <stdexcept>
class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error("Not implemented") { };
};

// Read one message from a topic, convert it to YAML, and print it to the terminal.
//
// This function will look up the topic via the ROS graph information to find the interface type.
// It then loads the type support and introspection information. The type support is used to
// subscribe to the topic and wait for a message. Upon reception of a message, the introspection
// library is used to read the binary data and convert it to a YAML representation.
int
echo_topic(
  rcl_node_t * node,
  const std::string & topic,
  const InterfaceTypeName &interface_type) {
  std::cout << "Waiting for message on topic '" << topic << "' with type " <<
    interface_type.first << '/' << interface_type.second << '\n';

  RosMessage message;
  if (dynmsg::c::ros_message_init(interface_type, &message) != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "Message init failed");
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("cli-tool", "Creating subscription");
  rcl_subscription_t sub = rcl_get_zero_initialized_subscription();
  rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
  const auto* type_support = get_type_support(interface_type);
  if (type_support == nullptr) {
    return 1;
  }
  auto ret = rcl_subscription_init(&sub, node, type_support, topic.c_str(), &sub_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "subscription init failed");
    return 1;
  }

  while (true) {
    size_t count{0};
    ret = rmw_subscription_count_matched_publishers(rcl_subscription_get_rmw_handle(&sub), &count);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("cli-tool", "publisher count failed");
      return 1;
    }
    RCUTILS_LOG_DEBUG_NAMED("cli-tool", "There are %ld matched publishers", count);
    if (count > 0) {
      break;
    }
    sleep(0.25);
  }

  bool taken = false;
  while (!taken) {
    taken = false;
    ret = rmw_take(rcl_subscription_get_rmw_handle(&sub), message.data, &taken, nullptr);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("cli-tool", "take failed");
      return 1;
    }
    if (taken) {
      RCUTILS_LOG_DEBUG_NAMED("cli-tool", "Received data");
      break;
    }
  }

  std::cout << dynmsg::c::message_to_yaml(message) << '\n';

  ret = rcl_subscription_fini(&sub, node);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "subscription fini failed");
    return 1;
  }
  return 0;
}


// Write the given ROS message (in YAML representation) to the specified topic.
//
// This function requires the interface type be specified, because the topic may not exist until it
// starts publishing data.
//
// This function will load the type support and introspection information for the provided
// interface type. It then converts the given YAML representation into a binary ROS message and
// stores it in a byte buffer. The type support is used to create a publisher to the given topic
// with the correct type, and then the ROS message is published to that topic ten times.
int publish_to_topic(
  rcl_node_t * node,
  const std::string & topic,
  const InterfaceTypeName &interface_type,
  const std::string & message_yaml)
{
  std::cout << "Publishing message on topic '" << topic << "' with type " <<
    interface_type.first << '/' << interface_type.second << '\n';

  RosMessage message = dynmsg::c::yaml_to_rosmsg(interface_type, message_yaml);

  RCUTILS_LOG_DEBUG_NAMED("cli-tool", "Creating publisher");
  rcl_publisher_t pub = rcl_get_zero_initialized_publisher();
  rcl_publisher_options_t pub_options = rcl_publisher_get_default_options();
  const auto* type_support = get_type_support(interface_type);
  if (type_support == nullptr) {
    return 1;
  }
  auto ret = rcl_publisher_init(&pub, node, type_support, topic.c_str(), &pub_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "subscription init failed");
    return 1;
  }

  for (auto ii = 0; ii < 10; ++ii) {
    std::cout << "Publishing\n";
    ret = rcl_publish(&pub, message.data, nullptr);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("cli-tool", "failed to publish message");
      return 1;
    }
    sleep(1);
  }

  ret = rcl_publisher_fini(&pub, node);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "publisher fini failed");
    return 1;
  }
  return 0;
}


// Print all known nodes from the ROS graph to the terminal.
//
// Only nodes known about at the time this function is called will be printed. It is recommended
// that some time be allowed to elapse (e.g. by calling a sleep) between calling rcl_init() and
// this function. This gives the underlying discovery system some time to find other nodes.
int print_nodes(const rcl_node_t* node) {
  auto names = rcutils_get_zero_initialized_string_array();
  auto namespaces = rcutils_get_zero_initialized_string_array();
  auto ret = rcl_get_node_names(node, rcl_get_default_allocator(), &names, &namespaces);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  std::cout << "nodes:" << std::endl;
  for (size_t i = 0; i < names.size; i++) {
    std::cout << "  " << names.data[i] << std::endl;
  }
  ret = rcutils_string_array_fini(&names);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  ret = rcutils_string_array_fini(&namespaces);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  return 0;
}


// Print all known topics from the ROS graph to the terminal.
//
// Only topics known about at the time this function is called will be printed. It is recommended
// that some time be allowed to elapse (e.g. by calling a sleep) between calling rcl_init() and
// this function. This gives the underlying discovery system some time to find topics.
int print_topics(const rcl_node_t* node) {
  auto topics = rcl_get_zero_initialized_names_and_types();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_get_topic_names_and_types(node, &allocator, false, &topics);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  std::cout << "topics:" << std::endl;
  for (size_t i = 0; i < topics.names.size; i++) {
    std::cout << "  " << topics.names.data[i] << " [" << topics.types[i].data[0] << "]" << std::endl;
  }
  ret = rcl_names_and_types_fini(&topics);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  return 0;
}


// Print all known services from the ROS graph to the terminal.
//
// Only services known about at the time this function is called will be printed. It is recommended
// that some time be allowed to elapse (e.g. by calling a sleep) between calling rcl_init() and
// this function. This gives the underlying discovery system some time to find services.
int print_services(const rcl_node_t* node) {
  auto services = rcl_get_zero_initialized_names_and_types();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_get_service_names_and_types(node, &allocator, &services);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  std::cout << "services:" << std::endl;
  for (size_t i = 0; i < services.names.size; i++) {
    std::cout << "  " << services.names.data[i]
      << " [" << services.types[i].data[0] << "]"
      << std::endl;
  }
  ret = rcl_names_and_types_fini(&services);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  return 0;
}


// Print all known actions from the ROS graph to the terminal.
//
// Only actions known about at the time this function is called will be printed. It is recommended
// that some time be allowed to elapse (e.g. by calling a sleep) between calling rcl_init() and
// this function. This gives the underlying discovery system some time to find actions.
int print_actions(const rcl_node_t* node) {
  auto actions = rcl_get_zero_initialized_names_and_types();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_action_get_names_and_types(node, &allocator, &actions);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  std::cout << "actions:" << std::endl;
  for (size_t i = 0; i < actions.names.size; i++) {
    std::cout << "  " << actions.names.data[i]
      << " [" << actions.types[i].data[0] << "]"
      << std::endl;
  }
  ret = rcl_names_and_types_fini(&actions);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "%s", rcl_get_error_string().str);
    return 1;
  }
  return 0;
}


int
main(int argc, char ** argv)
{
  auto args = parse_arguments(argc, argv);

  // Initialise the options for ROS
  rcl_init_options_t options = rcl_get_zero_initialized_init_options();
  rcl_ret_t ret = rcl_init_options_init(&options, rcl_get_default_allocator());
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "init options failed");
    return 1;
  }

  // Initialise ROS itself
  rcl_context_t context = rcl_get_zero_initialized_context();
  ret = rcl_init(argc, argv, &options, &context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "init failed");
    return 1;
  }
  ret = rcl_init_options_fini(&options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "init_options fini failed");
    return 1;
  }

  // Create a node to get access to the ROS graph, topics, etc.
  RCUTILS_LOG_DEBUG_NAMED("cli-tool", "Creating node");
  rcl_node_options_t node_options = rcl_node_get_default_options();
  rcl_node_t node = rcl_get_zero_initialized_node();
  ret = rcl_node_init(&node, "clitool", "", &context, &node_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "node init failed");
    return 1;
  }

  try {
    InterfaceTypeName interface_type;
    switch (args.cmd) {
      case Command::TopicEcho:
        // Need to sleep for abit for discovery to populate the ROS graph information so we can get
        // the topic type automatically
        std::this_thread::sleep_for(std::chrono::seconds(1));

        interface_type = get_topic_type(&node, args.params["topic"]);
        if (interface_type.first == "" || interface_type.second == "") {
          std::cout << "Unknown topic type '" << interface_type.first << '/' <<
            interface_type.second << "'\n";
          return 1;
        }
        return echo_topic(&node, args.params["topic"], interface_type);
      case Command::TopicPublish:
        interface_type = get_topic_type_from_string_type(args.params["type"]);
        if (interface_type.first == "" || interface_type.second == "") {
          std::cout << "Unknown topic type '" << interface_type.first << '/' <<
            interface_type.second << "'\n";
          return 1;
        }
        return publish_to_topic(&node, args.params["topic"], interface_type, args.params["msg"]);
      case Command::ServiceCall:
        throw NotImplemented();
      case Command::ServiceHost:
        throw NotImplemented();
      case Command::Discover: {
        // Need to sleep for abit for discovery to populate the ROS graph information
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return print_nodes(&node)
          || print_topics(&node)
          || print_services(&node)
          || print_actions(&node);
      }
      case Command::Unknown:
        std::cout << "Unknown command\n";
        return 1;
    };
  } catch (const std::runtime_error& e) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", e.what());
    return 1;
  }

  // Shut down and clean up
  ret = rcl_node_fini(&node);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "node fini failed");
    return 1;
  }
  ret = rcl_shutdown(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "shutdown failed");
    return 1;
  }
  ret = rcl_context_fini(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("cli-tool", "context fini failed");
    return 1;
  }
  return 0;
}
