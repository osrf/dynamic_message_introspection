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

#ifndef DYNMSG__MESSAGE_READING_HPP_
#define DYNMSG__MESSAGE_READING_HPP_

#include <yaml-cpp/yaml.h>

#include "dynmsg/typesupport.hpp"

namespace dynmsg
{

namespace c
{

/// Parse a ROS message stored in a raw buffer into a YAML representation.
/**
 * The "message" argument contains both a pointer to the raw buffer and a pointer to the ROS type's
 * introspection information as retrieved from an introspection type support library. (See the
 * "get_type_info" function in typesupport_utils.hpp for loading introspection type support.)
 *
 * This function will use the provided introspection information to read the binary data out of the
 * ROS message-containing raw buffer and convert it into a YAML representation. The YAML
 * representation is a tree structure, with each node in the tree being a field in the message.
 * Each field is represented by two values: the ROS type of the field, in a textual representation,
 * and the value. For an example of the YAML structure, run the CLI tool and echo a topic; the
 * resulting YAML printed to the terminal is the structure used.
 */
YAML::Node message_to_yaml(const RosMessage & message);

}  // namespace c

namespace cpp
{

/// C++ version of dynmsg::c::message_to_yaml().
/**
 * \see dynmsg::c::message_to_yaml()
 */
YAML::Node message_to_yaml(const RosMessage_Cpp & message);

/// Variant of dynmsg::cpp::message_to_yaml() for converting only selected members of a message into a YAML format.
/**
 * \details In order to decrease the overhead of converting full messages into their corresponding YAML format this
 *          function uses the type introspection information to convert solely the specified member. This member
 *          can either be a raw value or a message itself.
 *
 * \param message           ROS message to convert.
 * \param member_identifier Identifier of the member, multiple levels within the message are separated by '/'.
 * \return YAML representation of the selected member, will be null if the specified member is not part of the
 *         provided message.
 */
YAML::Node selected_member_to_yaml(const RosMessage_Cpp & message, const std::string &member_identifier);

}  // namespace cpp

}  // namespace dynmsg

#endif  // DYNMSG__MESSAGE_READING_HPP_
