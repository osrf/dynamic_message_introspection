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

#ifndef DYNMSG_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
#define DYNMSG_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_

#include <utility>
#include <string>

#include <rcutils/allocator.h>
#include <rosidl_typesupport_introspection_c/message_introspection.h>
#include <rosidl_typesupport_introspection_cpp/message_introspection.hpp>

// TODO(christophebedard) replace
typedef int32_t rcl_ret_t;

extern "C"
{

// Structure used to store the type support for a single interface type
using TypeSupport = rosidl_message_type_support_t;
// Structure used to store the introspection information for a single interface type
using TypeInfo_C = rosidl_typesupport_introspection_c__MessageMembers;
// Structure used to store the introspection information for a single field of a interface type
using MemberInfo_C = rosidl_typesupport_introspection_c__MessageMember;

// An interface type can be identified by its namespace (i.e. the package that stores it) and its
// type name
using InterfaceTypeName = std::pair<std::string, std::string>;

// A ROS message, stored in a binary buffer with attached introspection information
typedef struct RosMessage_C {
  const TypeInfo_C* type_info;
  uint8_t* data;
} RosMessage_C;

using TypeInfo = TypeInfo_C;
using MemberInfo = MemberInfo_C;
using RosMessage = RosMessage_C;

typedef const rosidl_message_type_support_t* (*get_message_ts_func)();

// Search for and load the introspection library for a single interface type.
// This function will search the system's configured library search paths (which should include the
// ROS paths) to find a dynamic library named following the pattern
// "lib[namespace]__rosidl_typesupport_introspection_c.so".
// When found, it opens that library and loads a function named following the pattern
// "rosidl_typesupport_introspection_c__get_message_type_support_handle__[namespace]__msg__[type]".
// This function, when called, provides a pointer to the introspection structure for the specified
// interface type. This pointer is returned. The information contained in this structure can be
// used to understand a ROS message stored in a binary buffer, or to construct a ROS message in a
// binary buffer.
const TypeInfo* get_type_info(const InterfaceTypeName &interface_type);

// Initialise a RosMessage structure.
// The introspection information for the specified interface type is loaded from its shared library
// and stored in the type_info field. The ros_msg buffer is allocated with enough space to store
// one ROS message of the specified type.
// When finshed with the RosMessage instance, call ros_message_destroy() to clean up allocated
// memory.
rcl_ret_t ros_message_init(const InterfaceTypeName &interface_type, RosMessage* ros_msg);

/// Version of ros_message_init() but with TypeInfo directly.
rcl_ret_t ros_message_init_(
  const TypeInfo * type_info,
  RosMessage* ros_msg,
  rcutils_allocator_t * allocator);

// Clean up a RosMessage instance by freeing its resources.
void ros_message_destroy(RosMessage* ros_msg);
void ros_message_destroy_(RosMessage* ros_msg, rcutils_allocator_t * allocator);

}  // extern "C"

using TypeInfo_Cpp = rosidl_typesupport_introspection_cpp::MessageMembers;
using MemberInfo_Cpp = rosidl_typesupport_introspection_cpp::MessageMember;

typedef struct RosMessage_Cpp {
  const TypeInfo_Cpp * type_info;
  uint8_t * data;
} RosMessage_Cpp;

const TypeInfo_Cpp * get_type_info_cpp(const InterfaceTypeName & interface_type);

#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
