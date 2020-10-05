#include "dynmsg_demo/typesupport_utils.hpp"

#include <dlfcn.h>

#include <sstream>

#include <rcl/graph.h>
#include <rcutils/logging_macros.h>


InterfaceTypeName get_topic_type(const rcl_node_t *node, const std::string &topic) {
  auto pubs = rcl_get_zero_initialized_topic_endpoint_info_array();
  auto allocator = rcl_get_default_allocator();
  auto ret = rcl_get_publishers_info_by_topic(node, &allocator, topic.data(), false, &pubs);
  if (ret != RCL_RET_OK || pubs.size <= 0) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "getting publishers failed");
    throw std::runtime_error(rcutils_get_error_string().str);
  }
  std::string topic_type(pubs.info_array->topic_type);
  std::string pkg = topic_type.substr(0, topic_type.find('/'));
  std::string name = topic_type.substr(topic_type.rfind('/') + 1);
  InterfaceTypeName int_type_name{pkg, name};

  ret = rcl_topic_endpoint_info_array_fini(&pubs, &allocator);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "cleaning up publishers failed");
    throw std::runtime_error(rcutils_get_error_string().str);
  }

  return int_type_name;
}


typedef const rosidl_message_type_support_t* (*get_message_ts_func)();

const TypeSupport* get_type_support(const InterfaceTypeName &interface_type) {
  std::string ts_lib_name;
  ts_lib_name = "lib" + interface_type.first + "__rosidl_typesupport_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading type support library %s",
    ts_lib_name.c_str());
  void * type_support_lib = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support library: %s", dlerror());
    return nullptr;
  }
  std::string ts_func_name;
  ts_func_name = "rosidl_typesupport_c__get_message_type_support_handle__" + interface_type.first +
    "__msg__" + interface_type.second;
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.c_str());

  get_message_ts_func type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(type_support_lib, ts_func_name.c_str()));
  if (type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support function: %s", dlerror());
    return nullptr;
  }

  const rosidl_message_type_support_t * ts = type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loaded type support %s", ts->typesupport_identifier);

  return ts;
}

const TypeInfo* get_type_info(const InterfaceTypeName &interface_type) {
  std::stringstream ts_lib_name;
  ts_lib_name << "lib" << interface_type.first << "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading introspection type support library %s",
    ts_lib_name.str().c_str());
  void * introspection_type_support_lib = dlopen(ts_lib_name.str().c_str(), RTLD_LAZY);
  if (introspection_type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load introspection type support library: %s", dlerror());
    return nullptr;
  }
  std::stringstream ts_func_name;
  ts_func_name << "rosidl_typesupport_introspection_c__get_message_type_support_handle__" << interface_type.first <<
    "__msg__" << interface_type.second;
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.str().c_str());

  get_message_ts_func introspection_type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(
      introspection_type_support_lib,
      ts_func_name.str().c_str()));
  if (introspection_type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg_demo",
      "failed to load introspection type support function: %s",
      dlerror());
    return nullptr;
  }

  const rosidl_message_type_support_t *introspection_ts = introspection_type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    introspection_ts->typesupport_identifier);
  const rosidl_typesupport_introspection_c__MessageMembers * type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(introspection_ts->data);

  return type_info;
}

rcl_ret_t ros_message_init(
  const InterfaceTypeName &interface_type,
  RosMessage* ros_msg
) {
  const auto* type_info = get_type_info(interface_type);
  if (type_info == nullptr) {
    return RCL_RET_ERROR;
  }
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Allocating message buffer of size %ld bytes",
    type_info->size_of_);
  uint8_t* data = new uint8_t[type_info->size_of_];
  type_info->init_function(data, ROSIDL_RUNTIME_C_MSG_INIT_DEFAULTS_ONLY);
  *ros_msg = RosMessage{ type_info, data };
  return RCL_RET_OK;
}

extern "C"
void ros_message_destroy(RosMessage* ros_msg) {
  ros_msg->type_info->fini_function(ros_msg->data);
  delete[] ros_msg->data;
}
