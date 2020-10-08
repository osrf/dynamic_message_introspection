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

extern "C"
RosMessage yaml_to_rosmsg(const InterfaceTypeName &interface_type, const std::string& yaml_str);

#endif  // DYNMSG_DEMO_INCLUDE_DYNMSG_DEMO_MSG_PARSER_HPP_
