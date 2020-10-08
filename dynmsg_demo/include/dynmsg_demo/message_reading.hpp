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

#ifndef DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MESSAGE_READING_HPP_
#define DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MESSAGE_READING_HPP_

#include <yaml-cpp/yaml.h>

// Forward declarations
struct RosMessage;

// Parse a ROS message stored in a raw buffer into a YAML representation.
// The "message" argument contains both a pointer to the raw buffer and a pointer to the ROS type's
// introspection information as retrieved from an introspection type support library. (See the
// "get_type_info" function in typesupport_utils.hpp for loading introspection type support.)
//
// This function will use the provided introspection information to read the binary data out of the
// ROS message-containing raw buffer and convert it into a YAML representation. The YAML
// representation is a tree structure, with each node in the tree being a field in the message.
// Each field is represented by two values: the ROS type of the field, in a textual representation,
// and the value. For an example of the YAML structure, run the CLI tool and echo a topic; the
// resulting YAML printed to the terminal is the structure used.
//
// This function will use the given type information to look for and open a type support library
// and an introspection library for the interface type. These two libraries must be present on the
// system and in the searched library paths. Typically if the interface type is being used on the
// local system then these two libraries will be available (if they are not then standard ROS nodes
// would also not be able to use that type).
//
// Once the type support libraries have been loaded, the type support library can be used to
// receive a message, e.g. by subscribing to a topic.
//
// Upon reception of a message, this function uses the introspection library to read the binary
// data and convert it to a YAML representation. 
YAML::Node message_to_yaml(const RosMessage &message);

#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MESSAGE_READING_HPP_
