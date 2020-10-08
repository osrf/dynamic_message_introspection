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

// Structure used to store the type support for a single message type
using TypeSupport = rosidl_message_type_support_t;
// Structure used to store the introspection information for a single interface type
using TypeInfo = rosidl_typesupport_introspection_c__MessageMembers;
// Structure used to store the introspection information for a single field of a interface type
using MemberInfo = rosidl_typesupport_introspection_c__MessageMember;

// An interface type can be identified by its namespace (i.e. the package that stores it) and its
// type name
using InterfaceTypeName = std::pair<std::string, std::string>;

// Get the type name of an existing topic.
// The topic must be being published or subscribed to by at least one node. If it is not, then the
// topic will not exist and so no type information will be retrievable.
// Additionally, the topic must have been discovered by this node. This may require waiting some
// time after starting calling rcl_init() for dynamic discovery to discover the topic.
InterfaceTypeName get_topic_type(const rcl_node_t *node, const std::string &topic);
// Split a type specified as a string into the namespace and type name.
// The string must be in the format "[namespace]/[type]", for example "example_interfaces/Int32".
InterfaceTypeName get_topic_type_from_string_type(const std::string &type);

const TypeSupport* get_type_support(const InterfaceTypeName &interface_type);
const TypeInfo* get_type_info(const InterfaceTypeName &interface_type);

/**
 * Wrapper to a generic ros message
 * */
typedef struct RosMessage {
  const TypeInfo* type_info;
  uint8_t* data;
} RosMessage;

rcl_ret_t ros_message_init(
  const InterfaceTypeName &interface_type,
  RosMessage* ros_msg
);

void ros_message_destroy(RosMessage* ros_msg);

};  // extern "C"
#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
