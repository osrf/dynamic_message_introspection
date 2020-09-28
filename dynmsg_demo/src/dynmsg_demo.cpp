#include <dlfcn.h>
#include <sstream>
#include <unistd.h>

#include <memory>

#include "rcl/rcl.h"
#include "rcl/context.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/subscription.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/field_types.h"

#include "rcutils/logging_macros.h"


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


std::stringstream print_message(
  const rosidl_typesupport_introspection_c__MessageMembers *type_info,
  std::shared_ptr<uint8_t> message)
{
  std::stringstream output;
  // Iterate over the message members
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Received message is of type %s/%s",
    type_info->message_namespace_,
    type_info->message_name_);
  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Message field values:");
  for (uint32_t ii = 0; ii < type_info->member_count_; ++ii) {
    RCUTILS_LOG_INFO_NAMED(
      "dynmsg_demo",
      "  %s (%s):\t%s",
      type_info->members_[ii].name_,
      member_type_to_string(type_info->members_[ii]),
      member_value_to_string(type_info->members_[ii], message).c_str());
  }
  return output;
}


int
main(int argc, char ** argv) {
  std::string msg_namespace(argv[1]);
  std::string msg_type(argv[2]);

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

  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Creating node");
  rcl_node_options_t node_options = rcl_node_get_default_options();
  rcl_node_t node = rcl_get_zero_initialized_node();
  ret = rcl_node_init(&node, "dynmsg_test", "", &context, &node_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node init failed");
    return 1;
  }

  std::stringstream ts_lib_name;
  ts_lib_name << "lib" << msg_namespace << "__rosidl_typesupport_c.so";
  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Loading type support library %s", ts_lib_name.str().c_str());
  void * type_support_lib = dlopen(ts_lib_name.str().c_str(), RTLD_LAZY);
  if (type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support library: %s", dlerror());
    return 1;
  }
  typedef const rosidl_message_type_support_t* (*get_message_ts_func)();
  std::stringstream ts_func_name;
  ts_func_name << "rosidl_typesupport_c__get_message_type_support_handle__" << msg_namespace <<
    "__msg__" << msg_type;
  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.str().c_str());
  get_message_ts_func type_support_handle_func = reinterpret_cast<get_message_ts_func>(dlsym(
    type_support_lib,
    ts_func_name.str().c_str()));
  if (type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support function: %s", dlerror());
    return 1;
  }
  const rosidl_message_type_support_t *ts = type_support_handle_func();
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    ts->typesupport_identifier);

  ts_lib_name.str(std::string());
  ts_lib_name << "lib" << msg_namespace << "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Loading introspection type support library %s",
    ts_lib_name.str().c_str());
  void * introspection_type_support_lib = dlopen(ts_lib_name.str().c_str(), RTLD_LAZY);
  if (introspection_type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load introspection type support library: %s", dlerror());
    return 1;
  }
  ts_func_name.str(std::string());
  ts_func_name << "rosidl_typesupport_introspection_c__get_message_type_support_handle__" << msg_namespace <<
    "__msg__" << msg_type;
  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.str().c_str());
  get_message_ts_func introspection_type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(
      introspection_type_support_lib,
      ts_func_name.str().c_str()));
  if (introspection_type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg_demo",
      "failed to load introspection type support function: %s",
      dlerror());
    return 1;
  }
  const rosidl_message_type_support_t *introspection_ts = introspection_type_support_handle_func();
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    introspection_ts->typesupport_identifier);
  const rosidl_typesupport_introspection_c__MessageMembers * type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(introspection_ts->data);

  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Creating subscription");
  rcl_subscription_t sub = rcl_get_zero_initialized_subscription();
  rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
  ret = rcl_subscription_init(&sub, &node, ts, "dynmsg", &sub_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "subscription init failed");
    return 1;
  }

  bool running = true;
  while(running) {
    size_t count{0};
    ret = rmw_subscription_count_matched_publishers(rcl_subscription_get_rmw_handle(&sub), &count);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "pub count failed");
      return 1;
    }
    RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "There are %ld matched publishers", count);
    if (count > 0) {
      break;
    }
    sleep(0.25);
  }

  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Allocating message buffer of size %ld bytes",
    type_info->size_of_);
  std::shared_ptr<uint8_t> message(new uint8_t[type_info->size_of_]);

  bool taken = false;
  while(!taken) {
    taken = false;
    ret = rmw_take(rcl_subscription_get_rmw_handle(&sub), message.get(), &taken, nullptr);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "take failed");
      return 1;
    }
    if (taken) {
      RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Received data");
      break;
    }
  }

  print_message(type_info, message);

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
