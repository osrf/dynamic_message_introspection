// Copyright 2020 Open Source Robotics Foundation, Inc.
// Copyright 2021 Christophe Bedard
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

#include <dlfcn.h>

#include <sstream>
#include <string>

#include "rcutils/allocator.h"
#include "rcutils/logging_macros.h"

#include "dynmsg/types.h"
#include "dynmsg/typesupport.hpp"

namespace dynmsg
{

namespace c
{

const TypeInfo * get_type_info(const InterfaceTypeName & interface_type)
{
  // Load the introspection library for the package containing the requested type
  std::stringstream ts_lib_name;
  ts_lib_name << "lib" << interface_type.first << "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Loading introspection type support library %s",
    ts_lib_name.str().c_str());
  void * introspection_type_support_lib = dlopen(ts_lib_name.str().c_str(), RTLD_LAZY);
  if (introspection_type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg", "failed to load introspection type support library: %s", dlerror());
    return nullptr;
  }
  // Load the function that, when called, will give us the introspection information for the
  // interface type we are interested in
  std::stringstream ts_func_name;
  ts_func_name << "rosidl_typesupport_introspection_c__get_message_type_support_handle__" <<
    interface_type.first << "__msg__" << interface_type.second;
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg", "Loading type support function %s", ts_func_name.str().c_str());

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
  const rosidl_message_type_support_t * introspection_ts =
    introspection_type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Loaded type support %s",
    introspection_ts->typesupport_identifier);
  const rosidl_typesupport_introspection_c__MessageMembers * type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
    introspection_ts->data);

  return type_info;
}

dynmsg_ret_t ros_message_with_typeinfo_init(
  const TypeInfo * type_info,
  RosMessage * ros_msg,
  rcutils_allocator_t * allocator)
{
  rcutils_allocator_t default_allocator = rcutils_get_default_allocator();
  if (!allocator) {
    allocator = &default_allocator;
  }
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Allocating message buffer of size %ld bytes",
    type_info->size_of_);
  // Allocate space to store the binary representation of the message
  uint8_t * data =
    static_cast<uint8_t *>(allocator->allocate(type_info->size_of_, allocator->state));
  if (nullptr == data) {
    return DYNMSG_RET_ERROR;
  }
  // Initialise the message buffer according to the interface type
  type_info->init_function(data, ROSIDL_RUNTIME_C_MSG_INIT_ALL);
  *ros_msg = RosMessage{type_info, data};
  return DYNMSG_RET_OK;
}

dynmsg_ret_t ros_message_init(
  const InterfaceTypeName & interface_type,
  RosMessage * ros_msg)
{
  const auto * type_info = get_type_info(interface_type);
  if (nullptr == type_info) {
    return DYNMSG_RET_ERROR;
  }
  return dynmsg::c::ros_message_with_typeinfo_init(type_info, ros_msg, nullptr);
}

void ros_message_destroy_with_allocator(RosMessage * ros_msg, rcutils_allocator_t * allocator)
{
  ros_msg->type_info->fini_function(ros_msg->data);
  allocator->deallocate(ros_msg->data, allocator->state);
}

void ros_message_destroy(RosMessage * ros_msg)
{
  ros_msg->type_info->fini_function(ros_msg->data);
  delete[] ros_msg->data;
}

}  // namespace c

namespace cpp
{

const TypeInfo_Cpp * get_type_info(const InterfaceTypeName & interface_type)
{
  const std::string pkg_name = interface_type.first;
  const std::string msg_name = interface_type.second;
  // Load the introspection library for the package containing the requested type
  std::string ts_lib_name = "lib" + pkg_name + "__rosidl_typesupport_introspection_cpp.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Loading C++ introspection type support library %s",
    ts_lib_name.c_str());
  void * introspection_type_support_lib = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (nullptr == introspection_type_support_lib) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg", "failed to load C++ introspection type support library: %s", dlerror());
    return nullptr;
  }

  // Load the function that, when called, will give us the introspection information for the
  // interface type we are interested in
  // The name here is mangled since this is C++. However, the mangling is fairly simple since it's
  // all the same. For example, we can get the symbols for a specific package this:
  //    $ nm install/[pkg name]/lib/lib[pkg name]__rosidl_typesupport_introspection_cpp.so | grep get_message_type_support_handle  # NOLINT
  // for std_msgs:
  //    $ nm install/std_msgs/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so | grep get_message_type_support_handle  # NOLINT
  // The first group is the unmangled C functions and the second one is the mangled C++ functions.
  // Given a package name and a message name, the symbol is thus:
  //    _ZN36rosidl_typesupport_introspection_cpp31get_message_type_support_handleIN[pkg name length][pkg name]3msg[msg name length + 1][msg name]_ISaIvEEEEEPK29rosidl_message_type_support_tv  // NOLINT
  // Example for std_msgs/msg/String:
  //    _ZN36rosidl_typesupport_introspection_cpp31get_message_type_support_handleIN8std_msgs3msg7String_ISaIvEEEEEPK29rosidl_message_type_support_tv  // NOLINT
  //      where:
  //        pkg name = std_msgs
  //        pkg name length = 8
  //        msg name = String
  //        msg name length + 1 = 6 + 1 = 7
  //          (this is because there is always a '_' in the internal template name at the end,
  //           e.g. 'String_')
  std::string ts_func_name =
    "_ZN36rosidl_typesupport_introspection_cpp31get_message_type_support_handleIN" +
    std::to_string(pkg_name.length()) + pkg_name + "3msg" +
    std::to_string(msg_name.length() + 1) + msg_name +
    "_ISaIvEEEEEPK29rosidl_message_type_support_tv";
  RCUTILS_LOG_DEBUG_NAMED("dynmsg", "Loading C++ type support function %s", ts_func_name.c_str());

  get_message_ts_func introspection_type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(
      introspection_type_support_lib,
      ts_func_name.c_str()));
  if (nullptr == introspection_type_support_handle_func) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg",
      "failed to load C++ introspection type support function: %s",
      dlerror());
    return nullptr;
  }

  // Call the function to get the introspection information we want
  const rosidl_message_type_support_t * introspection_ts = introspection_type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Loaded C++ type support %s",
    introspection_ts->typesupport_identifier);
  const TypeInfo_Cpp * type_info = reinterpret_cast<const TypeInfo_Cpp *>(introspection_ts->data);

  return type_info;
}

dynmsg_ret_t ros_message_with_typeinfo_init(
  const TypeInfo_Cpp * type_info,
  RosMessage_Cpp * ros_msg,
  rcutils_allocator_t * allocator)
{
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg",
    "Allocating message buffer of size %ld bytes",
    type_info->size_of_);
  // Allocate space to store the binary representation of the message
  uint8_t * data =
    static_cast<uint8_t *>(allocator->allocate(type_info->size_of_, allocator->state));
  if (nullptr == data) {
    return DYNMSG_RET_ERROR;
  }
  // Initialise the message buffer according to the interface type
  type_info->init_function(data, rosidl_runtime_cpp::MessageInitialization::ALL);
  *ros_msg = RosMessage_Cpp{type_info, data};
  return DYNMSG_RET_OK;
}

void ros_message_destroy_with_allocator(RosMessage_Cpp * ros_msg, rcutils_allocator_t * allocator)
{
  ros_msg->type_info->fini_function(ros_msg->data);
  allocator->deallocate(ros_msg->data, allocator->state);
}

}  // namespace cpp

}  // namespace dynmsg
