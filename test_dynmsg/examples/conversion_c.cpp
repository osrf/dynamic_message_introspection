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

#include <yaml-cpp/yaml.h>

#include <string>

#include "dynmsg/message_reading.hpp"
#include "dynmsg/msg_parser.hpp"
#include "dynmsg/typesupport.hpp"
#include "dynmsg/yaml_utils.hpp"

#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "rosidl_runtime_c/string_functions.h"
#include "std_msgs/msg/header.h"

int main()
{
  // Start with a ROS 2 message, like a std_msgs/Header
  std_msgs__msg__Header * msg = std_msgs__msg__Header__create();
  msg->stamp.sec = 4;
  msg->stamp.nanosec = 20u;
  rosidl_runtime_c__String__assign(&msg->frame_id, "my_frame");

  // Convert it into a YAML representation
  RosMessage_C ros_msg;
  // Note: type support info could be retrieved through other means, see dynmsg::cpp::*
  InterfaceTypeName interface{"std_msgs", "Header"};
  ros_msg.type_info = dynmsg::c::get_type_info(interface);
  ros_msg.data = reinterpret_cast<uint8_t *>(msg);
  YAML::Node yaml_msg = dynmsg::c::message_to_yaml(ros_msg);

  // Convert the YAML representation to a string
  const std::string yaml_string = dynmsg::yaml_to_string(yaml_msg);
  // Prints normal block-style YAML:
  //   stamp:
  //     sec: 4
  //     nanosec: 20
  //   frame_id: my_frame
  printf("%s\n", yaml_string.c_str());

  printf("\n");

  // Convert YAML string back to a ROS 2 message
  RosMessage_C ros_msg_from_yaml = dynmsg::c::yaml_to_rosmsg(interface, yaml_string);
  auto msg_from_yaml = reinterpret_cast<std_msgs__msg__Header *>(ros_msg_from_yaml.data);
  // Prints:
  //   my_frame
  //   4 s, 20 ns
  printf("%s\n", msg_from_yaml->frame_id.data);
  printf("%d s, %d ns\n", msg_from_yaml->stamp.sec, msg_from_yaml->stamp.nanosec);

  return 0;
}
