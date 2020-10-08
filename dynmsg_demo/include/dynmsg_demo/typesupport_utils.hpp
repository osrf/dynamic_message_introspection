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

#ifndef DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
#define DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_

#include <utility>
#include <string>

#include <rcl/types.h>
#include <rosidl_typesupport_introspection_c/message_introspection.h>


extern "C"
{

struct rcl_node_t;

// Structure used to store the type support for a single interface type
using TypeSupport = rosidl_message_type_support_t;
// Structure used to store the introspection information for a single interface type
using TypeInfo = rosidl_typesupport_introspection_c__MessageMembers;
// Structure used to store the introspection information for a single field of a interface type
using MemberInfo = rosidl_typesupport_introspection_c__MessageMember;

// An interface type can be identified by its namespace (i.e. the package that stores it) and its
// type name
using InterfaceTypeName = std::pair<std::string, std::string>;

// A ROS message, stored in a binary buffer with attached introspection information
typedef struct RosMessage {
  const TypeInfo* type_info;
  uint8_t* data;
} RosMessage;

// Get the type name of an existing topic.
// The topic must be being published or subscribed to by at least one node. If it is not, then the
// topic will not exist and so no type information will be retrievable.
// Additionally, the topic must have been discovered by this node. This may require waiting some
// time after starting calling rcl_init() for dynamic discovery to discover the topic.
InterfaceTypeName get_topic_type(const rcl_node_t *node, const std::string &topic);
// Split a type specified as a string into the namespace and type name.
// The string must be in the format "[namespace]/[type]", for example "example_interfaces/Int32".
InterfaceTypeName get_topic_type_from_string_type(const std::string &type);

// Search for and load the type support library for a single interface type.
// This function will search the system's configured library search paths (which should include the
// ROS paths) to find a dynamic library named following the pattern
// "lib[namespace]__rosidl_typesupport_c.so".
// When found, it opens that library and loads a function named following the pattern
// "rosidl_typesupport_c__get_message_type_support_handle__[namespace]__msg__[type]". This
// function, when called, provides a pointer to the type support structure for the specified
// interface type. This pointer is returned. It can be passed to functions such as
// rcl_subscription_init().
const TypeSupport* get_type_support(const InterfaceTypeName &interface_type);
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

// Clean up a RosMessage instance by freeing its resources.
void ros_message_destroy(RosMessage* ros_msg);

};  // extern "C"
#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
