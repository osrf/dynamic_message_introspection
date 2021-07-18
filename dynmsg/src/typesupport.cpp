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

#include "rcutils/allocator.h"

#include "dynmsg/typesupport.hpp"

#include <dlfcn.h>

#include <sstream>

#include <rcutils/logging_macros.h>

const TypeInfo* get_type_info(const InterfaceTypeName &interface_type) {
  // Load the introspection library for the package containing the requested type
  std::stringstream ts_lib_name;
  ts_lib_name << "lib" << interface_type.first << "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Loading introspection type support library %s",
    ts_lib_name.str().c_str());
  void * introspection_type_support_lib = dlopen(ts_lib_name.str().c_str(), RTLD_LAZY);
  if (introspection_type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg", "failed to load introspection type support library: %s", dlerror());
    return nullptr;
  }
  // Load the function that, when called, will give us the introspection information for the
  // interface type we are interested in
  std::stringstream ts_func_name;
  ts_func_name << "rosidl_typesupport_introspection_c__get_message_type_support_handle__" << interface_type.first <<
    "__msg__" << interface_type.second;
  RCUTILS_LOG_DEBUG_NAMED("dynmsg", "Loading type support function %s", ts_func_name.str().c_str());

  get_message_ts_func introspection_type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(
      introspection_type_support_lib,
      ts_func_name.str().c_str()));
  if (introspection_type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg",
      "failed to load introspection type support function: %s",
      dlerror());
    return nullptr;
  }

  // Call the function to get the introspection information we want
  const rosidl_message_type_support_t *introspection_ts = introspection_type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Loaded type support %s",
    introspection_ts->typesupport_identifier);
  const rosidl_typesupport_introspection_c__MessageMembers * type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(introspection_ts->data);

  return type_info;
}

rcl_ret_t ros_message_init_(
  const TypeInfo * type_info,
  RosMessage* ros_msg,
  rcutils_allocator_t * allocator
) {
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Allocating message buffer of size %ld bytes",
    type_info->size_of_);
  // Allocate space to store the binary representation of the message
  // uint8_t* data = new uint8_t[type_info->size_of_];
  uint8_t* data = static_cast<uint8_t *>(allocator->allocate(type_info->size_of_, allocator->state));
  if (nullptr == data) {
    return 1;
  }
  // Initialise the message buffer according to the interface type
  type_info->init_function(data, ROSIDL_RUNTIME_C_MSG_INIT_DEFAULTS_ONLY);
  *ros_msg = RosMessage{ type_info, data };
  return 0;
}

rcl_ret_t ros_message_init(
  const InterfaceTypeName &interface_type,
  RosMessage* ros_msg
) {
  const auto* type_info = get_type_info(interface_type);
  if (type_info == nullptr) {
    return 1;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  return ros_message_init_(type_info, ros_msg, &allocator);
}

extern "C"
void ros_message_destroy_(RosMessage* ros_msg, rcutils_allocator_t * allocator) {
  ros_msg->type_info->fini_function(ros_msg->data);
  allocator->deallocate(ros_msg->data, allocator->state);
}

extern "C"
void ros_message_destroy(RosMessage* ros_msg) {
  ros_msg->type_info->fini_function(ros_msg->data);
  delete[] ros_msg->data;
}
