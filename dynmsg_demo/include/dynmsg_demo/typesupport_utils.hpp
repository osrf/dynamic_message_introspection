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


// forward declare
struct rcl_node_t;

using TypeSupport = rosidl_message_type_support_t;
using TypeInfo = rosidl_typesupport_introspection_c__MessageMembers;
using MemberInfo = rosidl_typesupport_introspection_c__MessageMember;

using InterfaceTypeName = std::pair<std::string, std::string>;

InterfaceTypeName get_topic_type(const rcl_node_t *node, const std::string &topic);
InterfaceTypeName get_topic_type_from_string_type(const std::string &type);

// TODO: export this?
const TypeSupport* get_type_support(const InterfaceTypeName &interface_type);
const TypeInfo* get_type_info(const InterfaceTypeName &interface_type);

/**
 * Wrapper to a generic ros message
 * */
extern "C"
typedef struct RosMessage {
  const TypeInfo* type_info;
  uint8_t* data;
} RosMessage;

extern "C"
rcl_ret_t ros_message_init(
  const InterfaceTypeName &interface_type,
  RosMessage* ros_msg
);

extern "C"
void ros_message_destroy(RosMessage* ros_msg);

#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
