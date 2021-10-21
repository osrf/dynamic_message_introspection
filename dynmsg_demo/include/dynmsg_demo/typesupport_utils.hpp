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

#include "dynmsg/typesupport.hpp"

#include <rcl/node.h>
#include <rcl/types.h>

extern "C"
{

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

}  // extern "C"
#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_TYPESUPPORT_UTILS_HPP_
