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

#include "dynmsg_demo/message_reading.hpp"
#include "dynmsg_demo/typesupport_utils.hpp"
#include "dynmsg_demo/string_utils.hpp"

#include <example_interfaces/msg/bool.h>
#include <example_interfaces/msg/byte.h>
#include <example_interfaces/msg/char.h>
#include <example_interfaces/msg/float32.h>
#include <example_interfaces/msg/float64.h>
#include <example_interfaces/msg/int8.h>
#include <example_interfaces/msg/u_int8.h>
#include <example_interfaces/msg/int16.h>
#include <example_interfaces/msg/u_int16.h>
#include <example_interfaces/msg/int32.h>
#include <example_interfaces/msg/u_int32.h>
#include <example_interfaces/msg/int64.h>
#include <example_interfaces/msg/u_int64.h>
#include <example_interfaces/msg/string.h>
#include <example_interfaces/msg/w_string.h>
#include <test_msgs/msg/arrays.h>
#include <test_msgs/msg/basic_types.h>
#include <test_msgs/msg/bounded_sequences.h>
#include <test_msgs/msg/unbounded_sequences.h>
#include <test_msgs/msg/nested.h>
#include <test_msgs/msg/strings.h>
#include <test_msgs/msg/w_strings.h>

#include <rosidl_runtime_c/primitives_sequence_functions.h>
#include <rosidl_runtime_c/string_functions.h>
#include <rosidl_runtime_c/u16string_functions.h>

#include <gtest/gtest.h>
#include <limits>

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
  almost_equal(T x, T y, int ulp)
{
  return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp ||
    std::fabs(x-y) < std::numeric_limits<T>::min();
}


TEST(ReadMsgBuffer, ReadBool)
{
  example_interfaces__msg__Bool * msg = example_interfaces__msg__Bool__create();
  msg->data = true;

  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Bool"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<bool>(), true);

  example_interfaces__msg__Bool__fini(msg);
}

TEST(ReadMsgBuffer, ReadByte)
{
  example_interfaces__msg__Byte * msg = example_interfaces__msg__Byte__create();
  msg->data = 0x42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Byte"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<uint8_t>(), 0x42);

  example_interfaces__msg__Byte__fini(msg);
}

TEST(ReadMsgBuffer, ReadChar)
{
  example_interfaces__msg__Char * msg = example_interfaces__msg__Char__create();
  msg->data = 'a';

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Char"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<uint8_t>(), 97);

  example_interfaces__msg__Char__fini(msg);
}

TEST(ReadMsgBuffer, ReadFloat32)
{
  example_interfaces__msg__Float32 * msg = example_interfaces__msg__Float32__create();
  msg->data = 42.42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Float32"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_TRUE(almost_equal(yaml_msg["data"]["value"].as<float>(), 42.42f, 2));

  example_interfaces__msg__Float32__fini(msg);
}

TEST(ReadMsgBuffer, ReadFloat64)
{
  example_interfaces__msg__Float64 * msg = example_interfaces__msg__Float64__create();
  msg->data = 42424242424242.42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Float64"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  output << std::fixed << std::setprecision(2);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_TRUE(almost_equal(yaml_msg["data"]["value"].as<double>(), 42424242424242.42, 2));

  output << std::defaultfloat << std::setprecision(6);
  example_interfaces__msg__Float64__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt8)
{
  example_interfaces__msg__Int8 * msg = example_interfaces__msg__Int8__create();
  msg->data = -42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Int8"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<int8_t>(), -42);

  example_interfaces__msg__Int8__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt8)
{
  example_interfaces__msg__UInt8 * msg = example_interfaces__msg__UInt8__create();
  msg->data = 142;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "UInt8"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<uint8_t>(), 142);

  example_interfaces__msg__UInt8__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt16)
{
  example_interfaces__msg__Int16 * msg = example_interfaces__msg__Int16__create();
  msg->data = -4242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Int16"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<int16_t>(), -4242);

  example_interfaces__msg__Int16__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt16)
{
  example_interfaces__msg__UInt16 * msg = example_interfaces__msg__UInt16__create();
  msg->data = 4242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "UInt16"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<uint16_t>(), 4242);

  example_interfaces__msg__UInt16__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt32)
{
  example_interfaces__msg__Int32 * msg = example_interfaces__msg__Int32__create();
  msg->data = -42424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Int32"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<int32_t>(), -42424242);

  example_interfaces__msg__Int32__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt32)
{
  example_interfaces__msg__UInt32 * msg = example_interfaces__msg__UInt32__create();
  msg->data = 4242424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "UInt32"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<uint32_t>(), 4242424242);

  example_interfaces__msg__UInt32__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt64)
{
  example_interfaces__msg__Int64 * msg = example_interfaces__msg__Int64__create();
  msg->data = -424242424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "Int64"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<int64_t>(), -424242424242l);

  example_interfaces__msg__Int64__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt64)
{
  example_interfaces__msg__UInt64 * msg = example_interfaces__msg__UInt64__create();
  msg->data = 424242424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"example_interfaces", "UInt64"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["data"]["value"].as<uint64_t>(), 424242424242ul);

  example_interfaces__msg__UInt64__fini(msg);
}

void populate_basic_types(test_msgs__msg__BasicTypes * msg)
{
  msg->bool_value = true;
  msg->byte_value = 142;
  msg->char_value = 42;
  msg->float32_value = 42.42;
  msg->float64_value = 4242424242424242.42;
  msg->int8_value = -42;
  msg->uint8_value = 242;
  msg->int16_value = -4242;
  msg->uint16_value = 4242;
  msg->int32_value = -42424242;
  msg->uint32_value = 4242424242;
  msg->int64_value = -424242424242;
  msg->uint64_value = 424242424242;
}

void compare_basic_types_item(YAML::Node yaml, test_msgs__msg__BasicTypes &msg)
{
  EXPECT_EQ(yaml["bool_value"]["type"].as<std::string>(), "boolean");
  EXPECT_EQ(yaml["bool_value"]["value"].as<bool>(), msg.bool_value);
  EXPECT_EQ(yaml["byte_value"]["type"].as<std::string>(), "octet");
  EXPECT_EQ(yaml["byte_value"]["value"].as<uint8_t>(), msg.byte_value);
  EXPECT_EQ(yaml["char_value"]["type"].as<std::string>(), "uint8");
  EXPECT_EQ(yaml["char_value"]["value"].as<uint8_t>(), msg.char_value);
  EXPECT_EQ(yaml["float32_value"]["type"].as<std::string>(), "float");
  EXPECT_EQ(yaml["float32_value"]["value"].as<float>(), msg.float32_value);
  EXPECT_EQ(yaml["float64_value"]["type"].as<std::string>(), "double");
  EXPECT_EQ(yaml["float64_value"]["value"].as<double>(), msg.float64_value);
  EXPECT_EQ(yaml["int8_value"]["type"].as<std::string>(), "int8");
  EXPECT_EQ(yaml["int8_value"]["value"].as<int8_t>(), msg.int8_value);
  EXPECT_EQ(yaml["uint8_value"]["type"].as<std::string>(), "uint8");
  EXPECT_EQ(yaml["uint8_value"]["value"].as<uint8_t>(), msg.uint8_value);
  EXPECT_EQ(yaml["int16_value"]["type"].as<std::string>(), "int16");
  EXPECT_EQ(yaml["int16_value"]["value"].as<int16_t>(), msg.int16_value);
  EXPECT_EQ(yaml["uint16_value"]["type"].as<std::string>(), "uint16");
  EXPECT_EQ(yaml["uint16_value"]["value"].as<uint16_t>(), msg.uint16_value);
  EXPECT_EQ(yaml["int32_value"]["type"].as<std::string>(), "int32");
  EXPECT_EQ(yaml["int32_value"]["value"].as<int32_t>(), msg.int32_value);
  EXPECT_EQ(yaml["uint32_value"]["type"].as<std::string>(), "uint32");
  EXPECT_EQ(yaml["uint32_value"]["value"].as<uint32_t>(), msg.uint32_value);
  EXPECT_EQ(yaml["int64_value"]["type"].as<std::string>(), "int64");
  EXPECT_EQ(yaml["int64_value"]["value"].as<int64_t>(), msg.int64_value);
  EXPECT_EQ(yaml["uint64_value"]["type"].as<std::string>(), "uint64");
  EXPECT_EQ(yaml["uint64_value"]["value"].as<uint64_t>(), msg.uint64_value);
}

TEST(ReadMsgBuffer, ReadArrays)
{
  test_msgs__msg__Arrays * msg = test_msgs__msg__Arrays__create();
  msg->bool_values[0] = true; msg->bool_values[1] = false; msg->bool_values[2] = true;
  msg->byte_values[0] = 0;
  msg->byte_values[1] = 127;
  msg->byte_values[2] = 255;
  msg->char_values[0] = 0;
  msg->char_values[1] = 127;
  msg->char_values[2] = 255;
  msg->float32_values[0] = 1e5;
  msg->float32_values[1] = 1e-5;
  msg->float32_values[2] = 1;
  msg->float64_values[0] = 1e10;
  msg->float64_values[1] = 1e-10;
  msg->float64_values[2] = 1;
  msg->int8_values[0] = -128;
  msg->int8_values[1] = 0;
  msg->int8_values[2] = 127;
  msg->uint8_values[0] = 0;
  msg->uint8_values[1] = 127;
  msg->uint8_values[2] = 255;
  msg->int16_values[0] = -32768;
  msg->int16_values[1] = 0;
  msg->int16_values[2] = 32767;
  msg->uint16_values[0] = 0;
  msg->uint16_values[1] = 32767;
  msg->uint16_values[2] = 65535;
  msg->int32_values[0] = -2147483648;
  msg->int32_values[1] = 0;
  msg->int32_values[2] = 2147483647;
  msg->uint32_values[0] = 0;
  msg->uint32_values[1] = 2147483647;
  msg->uint32_values[2] = 4294967295;
  msg->int64_values[0] = -9223372036854775807l;
  msg->int64_values[1] = 0;
  msg->int64_values[2] = 9223372036854775807l;
  msg->uint64_values[0] = std::numeric_limits<uint64_t>::min();
  msg->uint64_values[1] = 9223372036854775807ul;
  msg->uint64_values[2] = 18446744073709551615ul;
  rosidl_runtime_c__String__assign(&msg->string_values[0], "one");
  rosidl_runtime_c__String__assign(&msg->string_values[1], "two");
  rosidl_runtime_c__String__assign(&msg->string_values[2], "three");
  for (size_t ii = 0; ii < 3; ++ii) {
    populate_basic_types(&msg->basic_types_values[ii]);
  }
  msg->alignment_check = 42;

  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"test_msgs", "Arrays"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["bool_values"]["type"].as<std::string>(), "boolean[3]");
  EXPECT_EQ(
    yaml_msg["bool_values"]["value"].as<std::vector<bool>>(),
    (std::vector<bool>{true, false, true}));
  EXPECT_EQ(yaml_msg["byte_values"]["type"].as<std::string>(), "octet[3]");
  EXPECT_EQ(
    yaml_msg["byte_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 127, 255}));
  EXPECT_EQ(yaml_msg["char_values"]["type"].as<std::string>(), "uint8[3]");
  EXPECT_EQ(
    yaml_msg["char_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 127, 255}));
  EXPECT_EQ(yaml_msg["float32_values"]["type"].as<std::string>(), "float[3]");
  EXPECT_EQ(
    yaml_msg["float32_values"]["value"].as<std::vector<float>>(),
    (std::vector<float>{1e5, 1e-5, 1}));
  EXPECT_EQ(yaml_msg["float64_values"]["type"].as<std::string>(), "double[3]");
  EXPECT_EQ(
    yaml_msg["float64_values"]["value"].as<std::vector<double>>(),
    (std::vector<double>{1e10, 1e-10, 1}));
  EXPECT_EQ(yaml_msg["int8_values"]["type"].as<std::string>(), "int8[3]");
  EXPECT_EQ(
    yaml_msg["int8_values"]["value"].as<std::vector<int8_t>>(),
    (std::vector<int8_t>{-128, 0, 127}));
  EXPECT_EQ(yaml_msg["uint8_values"]["type"].as<std::string>(), "uint8[3]");
  EXPECT_EQ(
    yaml_msg["uint8_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 127, 255}));
  EXPECT_EQ(yaml_msg["int16_values"]["type"].as<std::string>(), "int16[3]");
  EXPECT_EQ(
    yaml_msg["int16_values"]["value"].as<std::vector<int16_t>>(),
    (std::vector<int16_t>{-32768, 0, 32767}));
  EXPECT_EQ(yaml_msg["uint16_values"]["type"].as<std::string>(), "uint16[3]");
  EXPECT_EQ(
    yaml_msg["uint16_values"]["value"].as<std::vector<uint16_t>>(),
    (std::vector<uint16_t>{0, 32767, 65535}));
  EXPECT_EQ(yaml_msg["int32_values"]["type"].as<std::string>(), "int32[3]");
  EXPECT_EQ(
    yaml_msg["int32_values"]["value"].as<std::vector<int32_t>>(),
    (std::vector<int32_t>{-2147483648, 0, 2147483647}));
  EXPECT_EQ(yaml_msg["uint32_values"]["type"].as<std::string>(), "uint32[3]");
  EXPECT_EQ(
    yaml_msg["uint32_values"]["value"].as<std::vector<uint32_t>>(),
    (std::vector<uint32_t>{0, 2147483647, 4294967295}));
  EXPECT_EQ(yaml_msg["int64_values"]["type"].as<std::string>(), "int64[3]");
  EXPECT_EQ(
    yaml_msg["int64_values"]["value"].as<std::vector<int64_t>>(),
    (std::vector<int64_t>{-9223372036854775807l, 0, 9223372036854775807l}));
  EXPECT_EQ(yaml_msg["uint64_values"]["type"].as<std::string>(), "uint64[3]");
  EXPECT_EQ(
    yaml_msg["uint64_values"]["value"].as<std::vector<uint64_t>>(),
    (std::vector<uint64_t>{0, 9223372036854775807ul, 18446744073709551615ul}));
  EXPECT_EQ(yaml_msg["string_values"]["type"].as<std::string>(), "string[3]");
  EXPECT_EQ(
    yaml_msg["string_values"]["value"].as<std::vector<std::string>>(),
    (std::vector<std::string>{"one", "two", "three"}));
  EXPECT_EQ(
    yaml_msg["basic_types_values"]["type"].as<std::string>(),
    "test_msgs__msg/BasicTypes[3]");
  for (auto array_item : yaml_msg["basic_types_values"]["value"]) {
    compare_basic_types_item(array_item, msg->basic_types_values[0]);
  }
  EXPECT_EQ(yaml_msg["alignment_check"]["type"].as<std::string>(), "int32");
  EXPECT_EQ(yaml_msg["alignment_check"]["value"].as<int32_t>(), 42);

  test_msgs__msg__Arrays__fini(msg);
}

TEST(ReadMsgBuffer, ReadBoundedSequences)
{
  test_msgs__msg__BoundedSequences * msg = test_msgs__msg__BoundedSequences__create();
  rosidl_runtime_c__boolean__Sequence__init(
    &msg->bool_values,
    test_msgs__msg__BoundedSequences__bool_values__MAX_SIZE);
  msg->bool_values.data[0] = true;
  msg->bool_values.data[1] = false;
  msg->bool_values.data[2] = true;
  rosidl_runtime_c__octet__Sequence__init(
    &msg->byte_values,
    test_msgs__msg__BoundedSequences__byte_values__MAX_SIZE);
  msg->byte_values.data[0] = 0;
  msg->byte_values.data[1] = 127;
  msg->byte_values.data[2] = 255;
  rosidl_runtime_c__uint8__Sequence__init(
    &msg->char_values,
    test_msgs__msg__BoundedSequences__char_values__MAX_SIZE);
  msg->char_values.data[0] = 0;
  msg->char_values.data[1] = 127;
  msg->char_values.data[2] = 255;
  rosidl_runtime_c__float__Sequence__init(
    &msg->float32_values,
    test_msgs__msg__BoundedSequences__float32_values__MAX_SIZE);
  msg->float32_values.data[0] = 1e5;
  msg->float32_values.data[1] = 1e-5;
  msg->float32_values.data[2] = 1;
  rosidl_runtime_c__double__Sequence__init(
    &msg->float64_values,
    test_msgs__msg__BoundedSequences__float64_values__MAX_SIZE);
  msg->float64_values.data[0] = 1e10;
  msg->float64_values.data[1] = 1e-10;
  msg->float64_values.data[2] = 1;
  rosidl_runtime_c__int8__Sequence__init(
    &msg->int8_values,
    test_msgs__msg__BoundedSequences__int8_values__MAX_SIZE);
  msg->int8_values.data[0] = -128;
  msg->int8_values.data[1] = 0;
  msg->int8_values.data[2] = 127;
  rosidl_runtime_c__uint8__Sequence__init(
    &msg->uint8_values,
    test_msgs__msg__BoundedSequences__uint8_values__MAX_SIZE);
  msg->uint8_values.data[0] = 0;
  msg->uint8_values.data[1] = 127;
  msg->uint8_values.data[2] = 255;
  rosidl_runtime_c__int16__Sequence__init(
    &msg->int16_values,
    test_msgs__msg__BoundedSequences__int16_values__MAX_SIZE);
  msg->int16_values.data[0] = -32768;
  msg->int16_values.data[1] = 0;
  msg->int16_values.data[2] = 32767;
  rosidl_runtime_c__uint16__Sequence__init(
    &msg->uint16_values,
    test_msgs__msg__BoundedSequences__uint16_values__MAX_SIZE);
  msg->uint16_values.data[0] = 0;
  msg->uint16_values.data[1] = 32767;
  msg->uint16_values.data[2] = 65535;
  rosidl_runtime_c__int32__Sequence__init(
    &msg->int32_values,
    test_msgs__msg__BoundedSequences__int32_values__MAX_SIZE);
  msg->int32_values.data[0] = -2147483648;
  msg->int32_values.data[1] = 0;
  msg->int32_values.data[2] = 2147483647;
  rosidl_runtime_c__uint32__Sequence__init(
    &msg->uint32_values,
    test_msgs__msg__BoundedSequences__uint32_values__MAX_SIZE);
  msg->uint32_values.data[0] = 0;
  msg->uint32_values.data[1] = 2147483647;
  msg->uint32_values.data[2] = 4294967295;
  rosidl_runtime_c__int64__Sequence__init(
    &msg->int64_values,
    test_msgs__msg__BoundedSequences__int64_values__MAX_SIZE);
  msg->int64_values.data[0] = -9223372036854775807l;
  msg->int64_values.data[1] = 0;
  msg->int64_values.data[2] = 9223372036854775807l;
  rosidl_runtime_c__uint64__Sequence__init(
    &msg->uint64_values,
    test_msgs__msg__BoundedSequences__uint64_values__MAX_SIZE);
  msg->uint64_values.data[0] = std::numeric_limits<uint64_t>::min();
  msg->uint64_values.data[1] = 9223372036854775807ul;
  msg->uint64_values.data[2] = 18446744073709551615ul;
  rosidl_runtime_c__String__Sequence__init(
    &msg->string_values,
    test_msgs__msg__BoundedSequences__string_values__MAX_SIZE);
  rosidl_runtime_c__String__assign(&msg->string_values.data[0], "one");
  rosidl_runtime_c__String__assign(&msg->string_values.data[1], "two");
  rosidl_runtime_c__String__assign(&msg->string_values.data[2], "three");
  test_msgs__msg__BasicTypes__Sequence__init(
    &msg->basic_types_values,
    test_msgs__msg__BoundedSequences__basic_types_values__MAX_SIZE);
  for (size_t ii = 0; ii < 3; ++ii) {
    populate_basic_types(&(msg->basic_types_values.data[ii]));
  }
  msg->alignment_check = 42;


  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"test_msgs", "BoundedSequences"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["bool_values"]["type"].as<std::string>(), "boolean[<=3]");
  EXPECT_EQ(
    yaml_msg["bool_values"]["value"].as<std::vector<bool>>(),
    (std::vector<bool>{true, false, true}));
  EXPECT_EQ(yaml_msg["byte_values"]["type"].as<std::string>(), "octet[<=3]");
  EXPECT_EQ(
    yaml_msg["byte_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 127, 255}));
  EXPECT_EQ(yaml_msg["char_values"]["type"].as<std::string>(), "uint8[<=3]");
  EXPECT_EQ(
    yaml_msg["char_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 127, 255}));
  EXPECT_EQ(yaml_msg["float32_values"]["type"].as<std::string>(), "float[<=3]");
  EXPECT_EQ(
    yaml_msg["float32_values"]["value"].as<std::vector<float>>(),
    (std::vector<float>{1e5, 1e-5, 1}));
  EXPECT_EQ(yaml_msg["float64_values"]["type"].as<std::string>(), "double[<=3]");
  EXPECT_EQ(
    yaml_msg["float64_values"]["value"].as<std::vector<double>>(),
    (std::vector<double>{1e10, 1e-10, 1}));
  EXPECT_EQ(yaml_msg["int8_values"]["type"].as<std::string>(), "int8[<=3]");
  EXPECT_EQ(
    yaml_msg["int8_values"]["value"].as<std::vector<int8_t>>(),
    (std::vector<int8_t>{-128, 0, 127}));
  EXPECT_EQ(yaml_msg["uint8_values"]["type"].as<std::string>(), "uint8[<=3]");
  EXPECT_EQ(
    yaml_msg["uint8_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 127, 255}));
  EXPECT_EQ(yaml_msg["int16_values"]["type"].as<std::string>(), "int16[<=3]");
  EXPECT_EQ(
    yaml_msg["int16_values"]["value"].as<std::vector<int16_t>>(),
    (std::vector<int16_t>{-32768, 0, 32767}));
  EXPECT_EQ(yaml_msg["uint16_values"]["type"].as<std::string>(), "uint16[<=3]");
  EXPECT_EQ(
    yaml_msg["uint16_values"]["value"].as<std::vector<uint16_t>>(),
    (std::vector<uint16_t>{0, 32767, 65535}));
  EXPECT_EQ(yaml_msg["int32_values"]["type"].as<std::string>(), "int32[<=3]");
  EXPECT_EQ(
    yaml_msg["int32_values"]["value"].as<std::vector<int32_t>>(),
    (std::vector<int32_t>{-2147483648, 0, 2147483647}));
  EXPECT_EQ(yaml_msg["uint32_values"]["type"].as<std::string>(), "uint32[<=3]");
  EXPECT_EQ(
    yaml_msg["uint32_values"]["value"].as<std::vector<uint32_t>>(),
    (std::vector<uint32_t>{0, 2147483647, 4294967295}));
  EXPECT_EQ(yaml_msg["int64_values"]["type"].as<std::string>(), "int64[<=3]");
  EXPECT_EQ(
    yaml_msg["int64_values"]["value"].as<std::vector<int64_t>>(),
    (std::vector<int64_t>{-9223372036854775807l, 0, 9223372036854775807l}));
  EXPECT_EQ(yaml_msg["uint64_values"]["type"].as<std::string>(), "uint64[<=3]");
  EXPECT_EQ(
    yaml_msg["uint64_values"]["value"].as<std::vector<uint64_t>>(),
    (std::vector<uint64_t>{0, 9223372036854775807ul, 18446744073709551615ul}));
  EXPECT_EQ(yaml_msg["string_values"]["type"].as<std::string>(), "string[<=3]");
  EXPECT_EQ(
    yaml_msg["string_values"]["value"].as<std::vector<std::string>>(),
    (std::vector<std::string>{"one", "two", "three"}));
  EXPECT_EQ(
    yaml_msg["basic_types_values"]["type"].as<std::string>(),
    "test_msgs__msg/BasicTypes[<=3]");
  for (size_t ii = 0; ii < 3; ++ii) {
    compare_basic_types_item(yaml_msg["basic_types_values"]["value"][ii], msg->basic_types_values.data[ii]);
  }
  EXPECT_EQ(yaml_msg["alignment_check"]["type"].as<std::string>(), "int32");
  EXPECT_EQ(yaml_msg["alignment_check"]["value"].as<int32_t>(), 42);

  test_msgs__msg__BoundedSequences__fini(msg);
}

TEST(ReadMsgBuffer, ReadUnboundedSequences)
{
  test_msgs__msg__UnboundedSequences * msg = test_msgs__msg__UnboundedSequences__create();
  rosidl_runtime_c__boolean__Sequence__init(&msg->bool_values, 2);
  msg->bool_values.data[0] = true;
  msg->bool_values.data[1] = false;
  rosidl_runtime_c__octet__Sequence__init(&msg->byte_values, 2);
  msg->byte_values.data[0] = 0;
  msg->byte_values.data[1] = 255;
  rosidl_runtime_c__uint8__Sequence__init(&msg->char_values, 2);
  msg->char_values.data[0] = 0;
  msg->char_values.data[1] = 255;
  rosidl_runtime_c__float__Sequence__init(&msg->float32_values, 2);
  msg->float32_values.data[0] = 1e5;
  msg->float32_values.data[1] = 1e-5;
  rosidl_runtime_c__double__Sequence__init(&msg->float64_values, 2);
  msg->float64_values.data[0] = 1e10;
  msg->float64_values.data[1] = 1e-10;
  rosidl_runtime_c__int8__Sequence__init(&msg->int8_values, 2);
  msg->int8_values.data[0] = -128;
  msg->int8_values.data[1] = 127;
  rosidl_runtime_c__uint8__Sequence__init(&msg->uint8_values, 2);
  msg->uint8_values.data[0] = 0;
  msg->uint8_values.data[1] = 255;
  rosidl_runtime_c__int16__Sequence__init(&msg->int16_values, 2);
  msg->int16_values.data[0] = -32768;
  msg->int16_values.data[1] = 32767;
  rosidl_runtime_c__uint16__Sequence__init(&msg->uint16_values, 2);
  msg->uint16_values.data[0] = 0;
  msg->uint16_values.data[1] = 65535;
  rosidl_runtime_c__int32__Sequence__init(&msg->int32_values, 2);
  msg->int32_values.data[0] = -2147483648;
  msg->int32_values.data[1] = 2147483647;
  rosidl_runtime_c__uint32__Sequence__init(&msg->uint32_values, 2);
  msg->uint32_values.data[0] = 0;
  msg->uint32_values.data[1] = 4294967295;
  rosidl_runtime_c__int64__Sequence__init(&msg->int64_values, 2);
  msg->int64_values.data[0] = -9223372036854775807l;
  msg->int64_values.data[1] = 9223372036854775807l;
  rosidl_runtime_c__uint64__Sequence__init(&msg->uint64_values, 2);
  msg->uint64_values.data[0] = std::numeric_limits<uint64_t>::min();
  msg->uint64_values.data[1] = 18446744073709551615ul;
  rosidl_runtime_c__String__Sequence__init(&msg->string_values, 2);
  rosidl_runtime_c__String__assign(&msg->string_values.data[0], "one");
  rosidl_runtime_c__String__assign(&msg->string_values.data[1], "two");
  test_msgs__msg__BasicTypes__Sequence__init(&msg->basic_types_values, 2);
  for (size_t ii = 0; ii < 2; ++ii) {
    populate_basic_types(&msg->basic_types_values.data[ii]);
  }
  msg->alignment_check = 42;

  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"test_msgs", "UnboundedSequences"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["bool_values"]["type"].as<std::string>(), "boolean[]");
  EXPECT_EQ(
    yaml_msg["bool_values"]["value"].as<std::vector<bool>>(),
    (std::vector<bool>{true, false}));
  EXPECT_EQ(yaml_msg["byte_values"]["type"].as<std::string>(), "octet[]");
  EXPECT_EQ(
    yaml_msg["byte_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 255}));
  EXPECT_EQ(yaml_msg["char_values"]["type"].as<std::string>(), "uint8[]");
  EXPECT_EQ(
    yaml_msg["char_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 255}));
  EXPECT_EQ(yaml_msg["float32_values"]["type"].as<std::string>(), "float[]");
  EXPECT_EQ(
    yaml_msg["float32_values"]["value"].as<std::vector<float>>(),
    (std::vector<float>{1e5, 1e-5}));
  EXPECT_EQ(yaml_msg["float64_values"]["type"].as<std::string>(), "double[]");
  EXPECT_EQ(
    yaml_msg["float64_values"]["value"].as<std::vector<double>>(),
    (std::vector<double>{1e10, 1e-10}));
  EXPECT_EQ(yaml_msg["int8_values"]["type"].as<std::string>(), "int8[]");
  EXPECT_EQ(
    yaml_msg["int8_values"]["value"].as<std::vector<int8_t>>(),
    (std::vector<int8_t>{-128, 127}));
  EXPECT_EQ(yaml_msg["uint8_values"]["type"].as<std::string>(), "uint8[]");
  EXPECT_EQ(
    yaml_msg["uint8_values"]["value"].as<std::vector<uint8_t>>(),
    (std::vector<uint8_t>{0, 255}));
  EXPECT_EQ(yaml_msg["int16_values"]["type"].as<std::string>(), "int16[]");
  EXPECT_EQ(
    yaml_msg["int16_values"]["value"].as<std::vector<int16_t>>(),
    (std::vector<int16_t>{-32768, 32767}));
  EXPECT_EQ(yaml_msg["uint16_values"]["type"].as<std::string>(), "uint16[]");
  EXPECT_EQ(
    yaml_msg["uint16_values"]["value"].as<std::vector<uint16_t>>(),
    (std::vector<uint16_t>{0, 65535}));
  EXPECT_EQ(yaml_msg["int32_values"]["type"].as<std::string>(), "int32[]");
  EXPECT_EQ(
    yaml_msg["int32_values"]["value"].as<std::vector<int32_t>>(),
    (std::vector<int32_t>{-2147483648, 2147483647}));
  EXPECT_EQ(yaml_msg["uint32_values"]["type"].as<std::string>(), "uint32[]");
  EXPECT_EQ(
    yaml_msg["uint32_values"]["value"].as<std::vector<uint32_t>>(),
    (std::vector<uint32_t>{0, 4294967295}));
  EXPECT_EQ(yaml_msg["int64_values"]["type"].as<std::string>(), "int64[]");
  EXPECT_EQ(
    yaml_msg["int64_values"]["value"].as<std::vector<int64_t>>(),
    (std::vector<int64_t>{-9223372036854775807l, 9223372036854775807l}));
  EXPECT_EQ(yaml_msg["uint64_values"]["type"].as<std::string>(), "uint64[]");
  EXPECT_EQ(
    yaml_msg["uint64_values"]["value"].as<std::vector<uint64_t>>(),
    (std::vector<uint64_t>{0, 18446744073709551615ul}));
  EXPECT_EQ(yaml_msg["string_values"]["type"].as<std::string>(), "string[]");
  EXPECT_EQ(
    yaml_msg["string_values"]["value"].as<std::vector<std::string>>(),
    (std::vector<std::string>{"one", "two"}));
  EXPECT_EQ(
    yaml_msg["basic_types_values"]["type"].as<std::string>(),
    "test_msgs__msg/BasicTypes[]");
  for (auto array_item : yaml_msg["basic_types_values"]["value"]) {
    compare_basic_types_item(array_item, msg->basic_types_values.data[0]);
  }
  EXPECT_EQ(yaml_msg["alignment_check"]["type"].as<std::string>(), "int32");
  EXPECT_EQ(yaml_msg["alignment_check"]["value"].as<int32_t>(), 42);

  test_msgs__msg__UnboundedSequences__fini(msg);
}

TEST(ReadMsgBuffer, Strings)
{
  test_msgs__msg__Strings * msg = test_msgs__msg__Strings__create();
  rosidl_runtime_c__String__assign(&msg->string_value, "forty two");
  rosidl_runtime_c__String__assign(&msg->bounded_string_value, "1234567890123456789012");

  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"test_msgs", "Strings"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["string_value"]["type"].as<std::string>(), "string");
  EXPECT_EQ(
    yaml_msg["string_value"]["value"].as<std::string>(), "forty two");
  EXPECT_EQ(yaml_msg["string_value_default1"]["type"].as<std::string>(), "string");
  EXPECT_EQ(
    yaml_msg["string_value_default1"]["value"].as<std::string>(), "Hello world!");
  EXPECT_EQ(yaml_msg["string_value_default2"]["type"].as<std::string>(), "string");
  EXPECT_EQ(
    yaml_msg["string_value_default2"]["value"].as<std::string>(), "Hello'world!");
  EXPECT_EQ(yaml_msg["string_value_default3"]["type"].as<std::string>(), "string");
  EXPECT_EQ(
    yaml_msg["string_value_default3"]["value"].as<std::string>(), "Hello\"world!");
  EXPECT_EQ(yaml_msg["string_value_default4"]["type"].as<std::string>(), "string");
  EXPECT_EQ(
    yaml_msg["string_value_default4"]["value"].as<std::string>(), "Hello'world!");
  EXPECT_EQ(yaml_msg["string_value_default5"]["type"].as<std::string>(), "string");
  EXPECT_EQ(
    yaml_msg["string_value_default5"]["value"].as<std::string>(), "Hello\"world!");

  EXPECT_EQ(yaml_msg["bounded_string_value"]["type"].as<std::string>(), "string<=22");
  EXPECT_EQ(
    yaml_msg["bounded_string_value"]["value"].as<std::string>(), "1234567890123456789012");
  EXPECT_EQ(yaml_msg["bounded_string_value_default1"]["type"].as<std::string>(), "string<=22");
  EXPECT_EQ(
    yaml_msg["bounded_string_value_default1"]["value"].as<std::string>(), "Hello world!");
  EXPECT_EQ(yaml_msg["bounded_string_value_default2"]["type"].as<std::string>(), "string<=22");
  EXPECT_EQ(
    yaml_msg["bounded_string_value_default2"]["value"].as<std::string>(), "Hello'world!");
  EXPECT_EQ(yaml_msg["bounded_string_value_default3"]["type"].as<std::string>(), "string<=22");
  EXPECT_EQ(
    yaml_msg["bounded_string_value_default3"]["value"].as<std::string>(), "Hello\"world!");
  EXPECT_EQ(yaml_msg["bounded_string_value_default4"]["type"].as<std::string>(), "string<=22");
  EXPECT_EQ(
    yaml_msg["bounded_string_value_default4"]["value"].as<std::string>(), "Hello'world!");
  EXPECT_EQ(yaml_msg["bounded_string_value_default5"]["type"].as<std::string>(), "string<=22");
  EXPECT_EQ(
    yaml_msg["bounded_string_value_default5"]["value"].as<std::string>(), "Hello\"world!");

  test_msgs__msg__Strings__fini(msg);
}

TEST(ReadMsgBuffer, WStrings)
{
  test_msgs__msg__WStrings * msg = test_msgs__msg__WStrings__create();
  rosidl_runtime_c__U16String__assign(
    &msg->wstring_value,
    reinterpret_cast<const uint16_t*>(u"四十二"));
  //rosidl_runtime_c__U16String__assign(
    //&msg->bounded_wstring_value,
    //reinterpret_cast<const uint16_t*>(u"二十二字以内の文字列"));
  rosidl_runtime_c__U16String__assign(
    &msg->array_of_wstrings[0],
    reinterpret_cast<const uint16_t*>(u"ワン"));
  rosidl_runtime_c__U16String__assign(
    &msg->array_of_wstrings[1],
    reinterpret_cast<const uint16_t*>(u"ツー"));
  rosidl_runtime_c__U16String__assign(
    &msg->array_of_wstrings[2],
    reinterpret_cast<const uint16_t*>(u"スリー"));
  rosidl_runtime_c__U16String__Sequence__init(
    &msg->bounded_sequence_of_wstrings,
    test_msgs__msg__WStrings__bounded_sequence_of_wstrings__MAX_SIZE);
  rosidl_runtime_c__U16String__assign(
    &msg->bounded_sequence_of_wstrings.data[0],
    reinterpret_cast<const uint16_t*>(u"ワン"));
  rosidl_runtime_c__U16String__assign(
    &msg->bounded_sequence_of_wstrings.data[1],
    reinterpret_cast<const uint16_t*>(u"ツー"));
  rosidl_runtime_c__U16String__assign(
    &msg->bounded_sequence_of_wstrings.data[2],
    reinterpret_cast<const uint16_t*>(u"スリー"));
  rosidl_runtime_c__U16String__Sequence__init(
    &msg->unbounded_sequence_of_wstrings,
    2);
  rosidl_runtime_c__U16String__assign(
    &msg->unbounded_sequence_of_wstrings.data[0],
    reinterpret_cast<const uint16_t*>(u"ワン"));
  rosidl_runtime_c__U16String__assign(
    &msg->unbounded_sequence_of_wstrings.data[1],
    reinterpret_cast<const uint16_t*>(u"ツー"));

  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"test_msgs", "WStrings"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["wstring_value"]["type"].as<std::string>(), "wstring");
  EXPECT_EQ(
    yaml_msg["wstring_value"]["value"].as<std::string>(),
    u16string_to_string(u"四十二"));
  EXPECT_EQ(yaml_msg["wstring_value_default1"]["type"].as<std::string>(), "wstring");
  EXPECT_EQ(
    yaml_msg["wstring_value_default1"]["value"].as<std::string>(),
    u16string_to_string(u"Hello world!"));
  EXPECT_EQ(yaml_msg["wstring_value_default2"]["type"].as<std::string>(), "wstring");
  EXPECT_EQ(
    yaml_msg["wstring_value_default2"]["value"].as<std::string>(),
    u16string_to_string(u"Hellö wörld!"));
  EXPECT_EQ(yaml_msg["wstring_value_default3"]["type"].as<std::string>(), "wstring");
  EXPECT_EQ(
    yaml_msg["wstring_value_default3"]["value"].as<std::string>(),
    u16string_to_string(u"ハローワールド"));

  EXPECT_EQ(yaml_msg["array_of_wstrings"]["type"].as<std::string>(), "wstring[3]");
  EXPECT_EQ(
    yaml_msg["array_of_wstrings"]["value"][0].as<std::string>(),
    u16string_to_string(u"ワン"));
  EXPECT_EQ(
    yaml_msg["array_of_wstrings"]["value"][1].as<std::string>(),
    u16string_to_string(u"ツー"));
  EXPECT_EQ(
    yaml_msg["array_of_wstrings"]["value"][2].as<std::string>(),
    u16string_to_string(u"スリー"));

  EXPECT_EQ(yaml_msg["bounded_sequence_of_wstrings"]["type"].as<std::string>(), "wstring[<=3]");
  EXPECT_EQ(
    yaml_msg["bounded_sequence_of_wstrings"]["value"][0].as<std::string>(),
    u16string_to_string(u"ワン"));
  EXPECT_EQ(
    yaml_msg["bounded_sequence_of_wstrings"]["value"][1].as<std::string>(),
    u16string_to_string(u"ツー"));
  EXPECT_EQ(
    yaml_msg["bounded_sequence_of_wstrings"]["value"][2].as<std::string>(),
    u16string_to_string(u"スリー"));

  EXPECT_EQ(yaml_msg["unbounded_sequence_of_wstrings"]["type"].as<std::string>(), "wstring[]");
  EXPECT_EQ(
    yaml_msg["unbounded_sequence_of_wstrings"]["value"][0].as<std::string>(),
    u16string_to_string(u"ワン"));
  EXPECT_EQ(
    yaml_msg["unbounded_sequence_of_wstrings"]["value"][1].as<std::string>(),
    u16string_to_string(u"ツー"));

  test_msgs__msg__WStrings__fini(msg);
}

TEST(ReadMsgBuffer, ReadNested)
{
  test_msgs__msg__Nested * msg = test_msgs__msg__Nested__create();
  populate_basic_types(&msg->basic_types_value);

  RosMessage message;
  message.type_info = get_type_info(InterfaceTypeName{"test_msgs", "Nested"});
  message.data = reinterpret_cast<uint8_t *>(msg);
  auto yaml_msg = message_to_yaml(message);

  EXPECT_EQ(yaml_msg["basic_types_value"]["type"].as<std::string>(), "test_msgs__msg/BasicTypes");
  compare_basic_types_item(yaml_msg["basic_types_value"]["value"], msg->basic_types_value);

  test_msgs__msg__Nested__fini(msg);
}
