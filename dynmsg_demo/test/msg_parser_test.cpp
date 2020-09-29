#include "../src/msg_parser.hpp"
#include "../src/typesupport_utils.hpp"

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <test_msgs/msg/basic_types.h>
#include <test_msgs/msg/defaults.h>

#include <yaml-cpp/yaml.h>

#include <limits>

#include <gtest/gtest.h>

TEST(MsgParser, Int32) {
  auto* typeinfo = get_type_info("std_msgs", "Int32");
  auto buffer = yaml_to_rosmsg("{ data: 123 }", typeinfo);

  std_msgs__msg__Int32 ros_msg{
    123,
  };

  std_msgs__msg__Int32* converted = reinterpret_cast<std_msgs__msg__Int32*>(buffer.data());

  EXPECT_EQ(converted->data, ros_msg.data);
}

TEST(MsgParser, String) {
  auto* typeinfo = get_type_info("std_msgs", "String");
  auto buffer = yaml_to_rosmsg("{ data: hello }", typeinfo);

  std_msgs__msg__String ros_msg{
    {
      "hello",
      5,
      6
    },
  };

  rosidl_runtime_c__String* created_msg =
    reinterpret_cast<rosidl_runtime_c__String*>(buffer.data());

  EXPECT_STREQ(created_msg->data, ros_msg.data.data);
}

TEST(MsgParser, BasicTypes) {
  auto* typeinfo = get_type_info("test_msgs", "BasicTypes");
  YAML::Node msg;
  msg["bool_value"] = true;
  msg["byte_value"] = std::numeric_limits<uint8_t>::max();
  msg["char_value"] = std::numeric_limits<uint8_t>::min();
  msg["float32_value"] = 1.1;
  msg["float64_value"] = 2.1;
  msg["int8_value"] = std::numeric_limits<int8_t>::min();
  msg["uint8_value"] = std::numeric_limits<uint8_t>::max();
  msg["int16_value"] = std::numeric_limits<int16_t>::min();
  msg["uint16_value"] = std::numeric_limits<uint16_t>::max();
  msg["int32_value"] = std::numeric_limits<int32_t>::min();
  msg["uint32_value"] = std::numeric_limits<uint32_t>::max();
  msg["int64_value"] = std::numeric_limits<int64_t>::min();
  msg["uint64_value"] = std::numeric_limits<uint64_t>::max();
  YAML::Emitter emitter;
  emitter << msg;
  auto buffer = yaml_to_rosmsg(emitter.c_str(), typeinfo);

  test_msgs__msg__BasicTypes ros_msg{
    true,
    std::numeric_limits<uint8_t>::max(),
    std::numeric_limits<uint8_t>::min(),
    1.1,
    2.1,
    std::numeric_limits<int8_t>::min(),
    std::numeric_limits<uint8_t>::max(),
    std::numeric_limits<int16_t>::min(),
    std::numeric_limits<uint16_t>::max(),
    std::numeric_limits<int32_t>::min(),
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<int64_t>::min(),
    std::numeric_limits<uint64_t>::max()
  };

  test_msgs__msg__BasicTypes* converted =
    reinterpret_cast<test_msgs__msg__BasicTypes*>(buffer.data());

  EXPECT_EQ(converted->bool_value, ros_msg.bool_value);
  EXPECT_EQ(converted->byte_value, ros_msg.byte_value);
  EXPECT_EQ(converted->char_value, ros_msg.char_value);
  EXPECT_EQ(converted->float32_value, ros_msg.float32_value);
  EXPECT_EQ(converted->float64_value, ros_msg.float64_value);
  EXPECT_EQ(converted->int8_value, ros_msg.int8_value);
  EXPECT_EQ(converted->uint8_value, ros_msg.uint8_value);
  EXPECT_EQ(converted->int16_value, ros_msg.int16_value);
  EXPECT_EQ(converted->uint16_value, ros_msg.uint16_value);
  EXPECT_EQ(converted->int32_value, ros_msg.int32_value);
  EXPECT_EQ(converted->uint32_value, ros_msg.uint32_value);
  EXPECT_EQ(converted->int64_value, ros_msg.int64_value);
  EXPECT_EQ(converted->uint64_value, ros_msg.uint64_value);
}

TEST(MsgParser, Defaults) {
  auto* typeinfo = get_type_info("test_msgs", "Defaults");
  auto buffer = yaml_to_rosmsg("", typeinfo);

  test_msgs__msg__Defaults ros_msg{
    true,
    50,
    100,
    1.125,
    1.125,
    -50,
    200,
    -1000,
    2000,
    -30000,
    60000,
    -40000000,
    50000000,
  };

  test_msgs__msg__BasicTypes* converted =
    reinterpret_cast<test_msgs__msg__BasicTypes*>(buffer.data());

  EXPECT_EQ(converted->bool_value, ros_msg.bool_value);
  EXPECT_EQ(converted->byte_value, ros_msg.byte_value);
  EXPECT_EQ(converted->char_value, ros_msg.char_value);
  EXPECT_EQ(converted->float32_value, ros_msg.float32_value);
  EXPECT_EQ(converted->float64_value, ros_msg.float64_value);
  EXPECT_EQ(converted->int8_value, ros_msg.int8_value);
  EXPECT_EQ(converted->uint8_value, ros_msg.uint8_value);
  EXPECT_EQ(converted->int16_value, ros_msg.int16_value);
  EXPECT_EQ(converted->uint16_value, ros_msg.uint16_value);
  EXPECT_EQ(converted->int32_value, ros_msg.int32_value);
  EXPECT_EQ(converted->uint32_value, ros_msg.uint32_value);
  EXPECT_EQ(converted->int64_value, ros_msg.int64_value);
  EXPECT_EQ(converted->uint64_value, ros_msg.uint64_value);
}
