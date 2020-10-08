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

#ifndef DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MSG_PARSER_HPP_
#define DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MSG_PARSER_HPP_

#include "typesupport_utils.hpp"

#include <vector>

// Parse a YAML representation of a message into a ROS message and store it in a raw buffer.
// The interface type must be specified as namespace and type, where a string representation would
// be "namespace/Type", for example "example_interfaces/Int32".
//
// This function will use the given type information to look for and open a type support library
// and an introspection library for the interface type. These two libraries must be present on the
// system and in the searched library paths. Typically if the interface type is being used on the
// local system then these two libraries will be available (if they are not then standard ROS nodes
// would also not be able to use that type).
//
// Once the type support libraries have been loaded, the introspection library is used to convert
// the YAML representation into the correct binary representation for the given ROS message.
//
// Upon reception of a message, the introspection library is used to read the binary data and
// convert it to a YAML representation. The YAML representation is a tree structure, with each node
// in the tree being a field in the message. Each field is represented by two values: the ROS type
// of the field, in a textual representation, and the value. For an example of the YAML structure,
// run the CLI tool and echo a topic; the resulting YAML printed to the terminal is the structure
// used.
extern "C"
RosMessage yaml_to_rosmsg(const InterfaceTypeName &interface_type, const std::string& yaml_str);

#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MSG_PARSER_HPP_
