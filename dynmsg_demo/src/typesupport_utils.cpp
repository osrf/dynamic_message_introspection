#include "typesupport_utils.hpp"

#include <rcutils/logging_macros.h>

#include <dlfcn.h>

#include <sstream>

typedef const rosidl_message_type_support_t* (*get_message_ts_func)();

const TypeSupport* get_type_support(const std::string& msg_namespace, const std::string& msg_type) {
  std::string ts_lib_name;
  ts_lib_name = "lib" + msg_namespace + "__rosidl_typesupport_c.so";
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Loading type support library %s",
    ts_lib_name.c_str());
  void * type_support_lib = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support library: %s", dlerror());
    return nullptr;
  }
  std::string ts_func_name;
  ts_func_name = "rosidl_typesupport_c__get_message_type_support_handle__" + msg_namespace +
    "__msg__" + msg_type;
  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.c_str());

  get_message_ts_func type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(type_support_lib, ts_func_name.c_str()));
  if (type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support function: %s", dlerror());
    return nullptr;
  }

  const rosidl_message_type_support_t * ts = type_support_handle_func();
  RCUTILS_LOG_INFO_NAMED("dynmsg_demo", "Loaded type support %s", ts->typesupport_identifier);

  return ts;
}

const TypeInfo* get_type_info(const std::string& msg_namespace, const std::string& msg_type) {
  std::stringstream ts_lib_name;
  ts_lib_name << "lib" << msg_namespace << "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Loading introspection type support library %s",
    ts_lib_name.str().c_str());
  void * introspection_type_support_lib = dlopen(ts_lib_name.str().c_str(), RTLD_LAZY);
  if (introspection_type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load introspection type support library: %s", dlerror());
    return nullptr;
  }
  std::stringstream ts_func_name;
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
    return nullptr;
  }

  const rosidl_message_type_support_t *introspection_ts = introspection_type_support_handle_func();
  RCUTILS_LOG_INFO_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    introspection_ts->typesupport_identifier);
  const rosidl_typesupport_introspection_c__MessageMembers * type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(introspection_ts->data);

  return type_info;
}

rcl_ret_t ros_message_init(
  const char* msg_namespace,
  const char* msg_type,
  RosMessage* ros_msg
) {
  const auto* type_info = get_type_info(msg_namespace, msg_type);
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
