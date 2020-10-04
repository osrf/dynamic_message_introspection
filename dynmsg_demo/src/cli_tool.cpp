#include "dynmsg_demo/cli.hpp"
#include "dynmsg_demo/message_reading.hpp"
#include "dynmsg_demo/typesupport_utils.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>

#include "rcl/context.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/rcl.h"
#include "rcl/subscription.h"
#include "rcl/types.h"

#include "rcutils/logging_macros.h"


int
main(int argc, char ** argv) {
  auto args = parse_arguments(argc, argv);

  //std::string msg_namespace(argv[1]);
  //std::string msg_type(argv[2]);

  //rcl_init_options_t options = rcl_get_zero_initialized_init_options();
  //rcl_ret_t ret = rcl_init_options_init(&options, rcl_get_default_allocator());
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init options failed");
    //return 1;
  //}

  //rcl_context_t context = rcl_get_zero_initialized_context();
  //ret = rcl_init(argc, argv, &options, &context);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init failed");
    //return 1;
  //}
  //ret = rcl_init_options_fini(&options);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init_options fini failed");
    //return 1;
  //}

  //RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating node");
  //rcl_node_options_t node_options = rcl_node_get_default_options();
  //rcl_node_t node = rcl_get_zero_initialized_node();
  //ret = rcl_node_init(&node, "dynmsg_test", "", &context, &node_options);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node init failed");
    //return 1;
  //}

  //RosMessage message;
  //if (ros_message_init(msg_namespace.c_str(), msg_type.c_str(), &message) != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "Message init failed");
    //return 1;
  //}

  //RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating subscription");
  //rcl_subscription_t sub = rcl_get_zero_initialized_subscription();
  //rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
  //const auto* type_support = get_type_support(msg_namespace, msg_type);
  //if (type_support == nullptr) {
    //return 1;
  //}
  //ret = rcl_subscription_init(&sub, &node, type_support, "dynmsg", &sub_options);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "subscription init failed");
    //return 1;
  //}

  //bool running = true;
  //while (running) {
    //size_t count{0};
    //ret = rmw_subscription_count_matched_publishers(rcl_subscription_get_rmw_handle(&sub), &count);
    //if (ret != RCL_RET_OK) {
      //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "pub count failed");
      //return 1;
    //}
    //RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "There are %ld matched publishers", count);
    //if (count > 0) {
      //break;
    //}
    //sleep(0.25);
  //}

  //bool taken = false;
  //while (!taken) {
    //taken = false;
    //ret = rmw_take(rcl_subscription_get_rmw_handle(&sub), message.data, &taken, nullptr);
    //if (ret != RCL_RET_OK) {
      //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "take failed");
      //return 1;
    //}
    //if (taken) {
      //RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Received data");
      //break;
    //}
  //}

  //std::stringstream output;
  //output << message.type_info->message_namespace_ << '/' <<
    //message.type_info->message_name_ << std::endl;
  //message_to_string(message, 1, output);
  //std::cout << output.str();

  //ret = rcl_node_fini(&node);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node fini failed");
    //return 1;
  //}
  //ret = rcl_shutdown(&context);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "shutdown failed");
    //return 1;
  //}
  //ret = rcl_context_fini(&context);
  //if (ret != RCL_RET_OK) {
    //RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "context fini failed");
    //return 1;
  //}
  return 0;
}
