#include "cli.hpp"

#include <dlfcn.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "rcl/context.h"
#include "rcl/graph.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/rcl.h"
#include "rcl/subscription.h"
#include "rcl/types.h"
#include "rcl_action/graph.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/field_types.h"

#include "rcutils/logging_macros.h"

void message_to_string(
  const rosidl_typesupport_introspection_c__MessageMembers * type_info,
  std::shared_ptr<uint8_t> message_data,
  size_t indent_level,
  std::stringstream &output);


const char *
member_type_to_string(const rosidl_typesupport_introspection_c__MessageMember &type_info)
{
  switch (type_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      return "float";
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      return "double";
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      return "long double";
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      return "char";
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      return "wchar";
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      return "boolean";
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      return "octet";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      return "uint8";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      return "int8";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      return "uint16";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      return "int16";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      return "uint32";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      return "int32";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      return "uint64";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      return "int64";
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      return "string";
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      return "wstring";
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      return "message";
    default:
      return "UNKNOWN";
  }
}


std::string
member_value_to_string(
  const rosidl_typesupport_introspection_c__MessageMember &type_info,
  std::shared_ptr<uint8_t> message_data)
{
  std::stringstream value;
  switch (type_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      float float_data;
      memcpy(&float_data, &message_data.get()[type_info.offset_], sizeof(float));
      value << float_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      double double_data;
      memcpy(&double_data, &message_data.get()[type_info.offset_], sizeof(double));
      value << double_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      long double ldouble_data;
      memcpy(&ldouble_data, &message_data.get()[type_info.offset_], sizeof(long double));
      value << ldouble_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      char char_data;
      memcpy(&char_data, &message_data.get()[type_info.offset_], sizeof(char));
      value << char_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      wchar_t wchar_t_data;
      memcpy(&wchar_t_data, &message_data.get()[type_info.offset_], sizeof(wchar_t));
      value << wchar_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      bool bool_data;
      memcpy(&bool_data, &message_data.get()[type_info.offset_], sizeof(bool));
      value << bool_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      uint8_t octet_data;
      memcpy(&octet_data, &message_data.get()[type_info.offset_], sizeof(uint8_t));
      value << octet_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      uint8_t uint8_t_data;
      memcpy(&uint8_t_data, &message_data.get()[type_info.offset_], sizeof(uint8_t));
      value << uint8_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      int8_t int8_t_data;
      memcpy(&int8_t_data, &message_data.get()[type_info.offset_], sizeof(int8_t));
      value << int8_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      uint16_t uint16_t_data;
      memcpy(&uint16_t_data, &message_data.get()[type_info.offset_], sizeof(uint16_t));
      value << uint16_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      int16_t int16_t_data;
      memcpy(&int16_t_data, &message_data.get()[type_info.offset_], sizeof(int16_t));
      value << int16_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      uint32_t uint32_t_data;
      memcpy(&uint32_t_data, &message_data.get()[type_info.offset_], sizeof(uint32_t));
      value << uint32_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      int32_t int32_t_data;
      memcpy(&int32_t_data, &message_data.get()[type_info.offset_], sizeof(int32_t));
      value << int32_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      uint64_t uint64_t_data;
      memcpy(&uint64_t_data, &message_data.get()[type_info.offset_], sizeof(uint64_t));
      value << uint64_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      int64_t int64_t_data;
      memcpy(&int64_t_data, &message_data.get()[type_info.offset_], sizeof(int64_t));
      value << int64_t_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      char string_data[1024];
      strncpy(string_data, reinterpret_cast<const char*>(&message_data.get()[type_info.offset_]), 1024);
      value << string_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      char wstring_data[1024];
      memcpy(&wstring_data, &message_data.get()[type_info.offset_], type_info.array_size_);
      value << wstring_data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      value << "recursively handle sub-message here";
      break;
    default:
      value << "unknown value for unknown type";
      break;
  }
  return value.str();
}


void add_indent(size_t indent_level, std::stringstream &output)
{
  for (size_t ii = 0; ii < indent_level; ++ii) {
    output << "  ";
  }
}


void member_to_string(
  const rosidl_typesupport_introspection_c__MessageMember &member_info,
  std::shared_ptr<uint8_t> message_data,
  size_t indent_level,
  std::stringstream &output)
{
  if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
    // Nested message member
    const rosidl_typesupport_introspection_c__MessageMembers * nested_type_info =
      reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
        member_info.members_->data);
    add_indent(indent_level, output);
    output << member_info.name_ << " (" << nested_type_info->message_namespace_ <<
      '/' << nested_type_info->message_name_ << "):\n";
    message_to_string(
      nested_type_info,
      std::shared_ptr<uint8_t>(message_data, message_data.get() + member_info.offset_),
      indent_level + 1,
      output);
  } else {
    // POD member
    add_indent(indent_level, output);
    output << member_info.name_ << " (" <<
      member_type_to_string(member_info) << "):\t" <<
      member_value_to_string(member_info, message_data) << '\n';
  }
}


void message_to_string(
  const rosidl_typesupport_introspection_c__MessageMembers * type_info,
  std::shared_ptr<uint8_t> message_data,
  size_t indent_level,
  std::stringstream &output)
{
  for (uint32_t ii = 0; ii < type_info->member_count_; ++ii) {
    member_to_string(type_info->members_[ii], message_data, indent_level, output);
  }
}


typedef struct TypeSupport
{
  void * type_support_library;
  const rosidl_message_type_support_t * type_support;
  void * introspection_library;
  const rosidl_message_type_support_t * introspection;
  const rosidl_typesupport_introspection_c__MessageMembers * type_info;
} TypeSupport;


rcl_ret_t load_interface_type_support(
  const std::string &namespace_,
  const std::string &interface,
  TypeSupport &type_support)
{
  std::string ts_lib_name;
  ts_lib_name = "lib" + namespace_ + "__rosidl_typesupport_c.so";
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support library %s", ts_lib_name.c_str());
  type_support.type_support_library = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support.type_support_library == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support library: %s", dlerror());
    return RCL_RET_ERROR;
  }
  std::string ts_func_name;
  ts_func_name = "rosidl_typesupport_c__get_message_type_support_handle__" + namespace_ +
    "__msg__" + interface;
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading type support function %s",
    ts_func_name.c_str());
  typedef const rosidl_message_type_support_t* (*get_interface_ts_func)();
  get_interface_ts_func type_support_handle_func = reinterpret_cast<get_interface_ts_func>(dlsym(
    type_support.type_support_library,
    ts_func_name.c_str()));
  if (type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support function: %s", dlerror());
    return RCL_RET_ERROR;
  }
  type_support.type_support = type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    type_support.type_support->typesupport_identifier);

  ts_lib_name = "lib" + namespace_ + "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading introspection type support library %s",
    ts_lib_name.c_str());
  type_support.introspection_library = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support.introspection_library == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg_demo",
      "failed to load introspection type support library: %s",
      dlerror());
    return RCL_RET_ERROR;
  }
  ts_func_name = "rosidl_typesupport_introspection_c__get_message_type_support_handle__" +
    namespace_ + "__msg__" + interface;
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.c_str());
  get_interface_ts_func introspection_type_support_handle_func =
    reinterpret_cast<get_interface_ts_func>(dlsym(
      type_support.introspection_library,
      ts_func_name.c_str()));
  if (type_support.introspection_library == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg_demo",
      "failed to load introspection type support function: %s",
      dlerror());
    return RCL_RET_ERROR;
  }
  type_support.introspection = introspection_type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    type_support.introspection->typesupport_identifier);
  type_support.type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
      type_support.introspection->data);

  return RCL_RET_OK;
}


void print_nodes(const rcl_node_t* node) {
  auto names = rcutils_get_zero_initialized_string_array();
  auto namespaces = rcutils_get_zero_initialized_string_array();
  auto ret = rcl_get_node_names(node, rcl_get_default_allocator(), &names, &namespaces);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "discovering nodes failed");
    exit(1);
  }
  std::cout << "nodes:" << std::endl;
  for (size_t i = 0; i < names.size; i++) {
    std::cout << "  " << names.data[i] << std::endl;
  }
  ret = rcutils_string_array_fini(&names);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "deallocating names array failed");
    exit(1);
  }
  rcutils_string_array_fini(&namespaces);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "deallocating namespaces array failed");
    exit(1);
  }
}


void print_topics(const rcl_node_t* node) {
  auto topics = rcl_get_zero_initialized_names_and_types();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_get_topic_names_and_types(node, &allocator, false, &topics);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "discovering topics failed");
    exit(1);
  }
  std::cout << "topics:" << std::endl;
  for (size_t i = 0; i < topics.names.size; i++) {
    std::cout << "  " << topics.names.data[i] << " [" << topics.types[i].data[0] << "]" << std::endl;
  }
  ret = rcl_names_and_types_fini(&topics);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "destroying names and types failed");
    exit(1);
  }
}


void print_services(const rcl_node_t* node) {
  auto services = rcl_get_zero_initialized_names_and_types();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_get_service_names_and_types(node, &allocator, &services);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "discovering services failed");
    exit(1);
  }
  std::cout << "services:" << std::endl;
  for (size_t i = 0; i < services.names.size; i++) {
    std::cout << "  " << services.names.data[i]
      << " [" << services.types[i].data[0] << "]"
      << std::endl;
  }
  ret = rcl_names_and_types_fini(&services);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "destroying names and types failed");
    exit(1);
  }
}


void print_actions(const rcl_node_t* node) {
  auto actions = rcl_get_zero_initialized_names_and_types();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_action_get_names_and_types(node, &allocator, &actions);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "discovering actions failed");
    exit(1);
  }
  std::cout << "actions:" << std::endl;
  for (size_t i = 0; i < actions.names.size; i++) {
    std::cout << "  " << actions.names.data[i]
      << " [" << actions.types[i].data[0] << "]"
      << std::endl;
  }
  ret = rcl_names_and_types_fini(&actions);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "destroying names and types failed");
    exit(1);
  }
}


int
main(int argc, char ** argv) {
  auto args = parse_arguments(argc, argv);

  rcl_init_options_t options = rcl_get_zero_initialized_init_options();
  rcl_ret_t ret = rcl_init_options_init(&options, rcl_get_default_allocator());
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init options failed");
    return 1;
  }

  rcl_context_t context = rcl_get_zero_initialized_context();
  ret = rcl_init(argc, argv, &options, &context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init failed");
    return 1;
  }
  ret = rcl_init_options_fini(&options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init_options fini failed");
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating node");
  rcl_node_options_t node_options = rcl_node_get_default_options();
  rcl_node_t node = rcl_get_zero_initialized_node();
  ret = rcl_node_init(&node, "dynmsg_test", "", &context, &node_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node init failed");
    return 1;
  }

  // TODO: switch based on the cli command
  switch (args.cmd) {
    case Command::Discover: {
      // why do we need to wait for discovery to find the nodes?
      std::this_thread::sleep_for(std::chrono::seconds(1));
      print_nodes(&node);
      print_topics(&node);
      print_services(&node);
      print_actions(&node);
      exit(0);
    }
  }

  std::string msg_namespace(argv[1]);
  std::string msg_type(argv[2]);

  TypeSupport type_support;
  if (load_interface_type_support(msg_namespace, msg_type, type_support) != RCL_RET_OK) {
    // Error message already printed
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating subscription");
  rcl_subscription_t sub = rcl_get_zero_initialized_subscription();
  rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
  ret = rcl_subscription_init(&sub, &node, type_support.type_support, "dynmsg", &sub_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "subscription init failed");
    return 1;
  }

  bool running = true;
  while (running) {
    size_t count{0};
    ret = rmw_subscription_count_matched_publishers(rcl_subscription_get_rmw_handle(&sub), &count);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "pub count failed");
      return 1;
    }
    RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "There are %ld matched publishers", count);
    if (count > 0) {
      break;
    }
    sleep(0.25);
  }

  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Allocating message buffer of size %ld bytes",
    type_support.type_info->size_of_);
  std::shared_ptr<uint8_t> message(
    new uint8_t[type_support.type_info->size_of_],
    std::default_delete<uint8_t[]>());

  bool taken = false;
  while (!taken) {
    taken = false;
    ret = rmw_take(rcl_subscription_get_rmw_handle(&sub), message.get(), &taken, nullptr);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "take failed");
      return 1;
    }
    if (taken) {
      RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Received data");
      break;
    }
  }

  std::stringstream output;
  output << type_support.type_info->message_namespace_ << '/' <<
    type_support.type_info->message_name_ << '\n';
  message_to_string(type_support.type_info, message, 1, output);
  std::cout << output.str();

  ret = rcl_node_fini(&node);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node fini failed");
    return 1;
  }
  ret = rcl_shutdown(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "shutdown failed");
    return 1;
  }
  ret = rcl_context_fini(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "context fini failed");
    return 1;
  }
  return 0;
}
