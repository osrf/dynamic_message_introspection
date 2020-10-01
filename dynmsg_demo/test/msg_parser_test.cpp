#include "../src/msg_parser.hpp"
#include "../src/typesupport_utils.hpp"

#include <dynmsg_msgs/msg/wide_string.h>
#include <std_msgs/msg/string.h>
#include <test_msgs/msg/basic_types.h>
#include <test_msgs/msg/defaults.h>
#include <test_msgs/msg/nested.h>
#include <test_msgs/msg/arrays.h>

#include <yaml-cpp/yaml.h>

#include <limits>

#include <gtest/gtest.h>

YAML::Node basic_types_node() {
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
  return msg;
}

void set_basic_types(test_msgs__msg__BasicTypes& msg) {
  msg.bool_value = true;
  msg.byte_value = std::numeric_limits<uint8_t>::max();
  msg.char_value =  std::numeric_limits<uint8_t>::min();
  msg.float32_value = 1.1;
  msg.float64_value = 2.1;
  msg.int8_value = std::numeric_limits<int8_t>::min();
  msg.uint8_value = std::numeric_limits<uint8_t>::max();
  msg.int16_value = std::numeric_limits<int16_t>::min();
  msg.uint16_value = std::numeric_limits<uint16_t>::max();
  msg.int32_value = std::numeric_limits<int32_t>::min();
  msg.uint32_value = std::numeric_limits<uint32_t>::max();
  msg.int64_value = std::numeric_limits<int64_t>::min();
  msg.uint64_value = std::numeric_limits<uint64_t>::max();
}

void check_basic_types_values(
    const test_msgs__msg__BasicTypes* converted,
    const test_msgs__msg__BasicTypes* ros_msg
) {
  EXPECT_EQ(converted->bool_value, ros_msg->bool_value);
  EXPECT_EQ(converted->byte_value, ros_msg->byte_value);
  EXPECT_EQ(converted->char_value, ros_msg->char_value);
  EXPECT_EQ(converted->float32_value, ros_msg->float32_value);
  EXPECT_EQ(converted->float64_value, ros_msg->float64_value);
  EXPECT_EQ(converted->int8_value, ros_msg->int8_value);
  EXPECT_EQ(converted->uint8_value, ros_msg->uint8_value);
  EXPECT_EQ(converted->int16_value, ros_msg->int16_value);
  EXPECT_EQ(converted->uint16_value, ros_msg->uint16_value);
  EXPECT_EQ(converted->int32_value, ros_msg->int32_value);
  EXPECT_EQ(converted->uint32_value, ros_msg->uint32_value);
  EXPECT_EQ(converted->int64_value, ros_msg->int64_value);
  EXPECT_EQ(converted->uint64_value, ros_msg->uint64_value);
}

TEST(MsgParser, String) {
  std::string asd("asd");
  auto generic_msg = yaml_to_rosmsg("{ data: hello }", "std_msgs", "String");

  std_msgs__msg__String ros_msg{
    {
      "hello",
      5,
      6
    },
  };

  rosidl_runtime_c__String* created_msg =
    reinterpret_cast<rosidl_runtime_c__String*>(generic_msg.data);

  EXPECT_STREQ(created_msg->data, ros_msg.data.data);

  ros_message_destroy(&generic_msg);
}

TEST(MsgParser, WideString) {
  auto generic_msg = yaml_to_rosmsg("{ data: hello }", "dynmsg_msgs", "WideString");

  std::u16string ws(u"hello");
  dynmsg_msgs__msg__WideString ros_msg{
    {
      reinterpret_cast<uint_least16_t*>(const_cast<char16_t*>(ws.data())),
      // should these by the number of codepoints or the number of bytes?
      10,
      12
    },
  };

  rosidl_runtime_c__U16String* created_msg =
    reinterpret_cast<rosidl_runtime_c__U16String*>(generic_msg.data);

  std::u16string converted(reinterpret_cast<char16_t*>(created_msg->data));
  EXPECT_EQ(converted, ws);

  ros_message_destroy(&generic_msg);
}

TEST(MsgParser, BasicTypes) {
  YAML::Node msg = basic_types_node();
  YAML::Emitter emitter;
  emitter << msg;
  auto generic_msg = yaml_to_rosmsg(emitter.c_str(), "test_msgs", "BasicTypes");

  test_msgs__msg__BasicTypes ros_msg;
  set_basic_types(ros_msg);

  test_msgs__msg__BasicTypes* converted =
    reinterpret_cast<test_msgs__msg__BasicTypes*>(generic_msg.data);

  check_basic_types_values(converted, &ros_msg);

  ros_message_destroy(&generic_msg);
}

TEST(MsgParser, Defaults) {
  auto generic_msg = yaml_to_rosmsg("", "test_msgs", "Defaults");

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
    reinterpret_cast<test_msgs__msg__BasicTypes*>(generic_msg.data);

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

  ros_message_destroy(&generic_msg);
}

TEST(MsgParser, Nested) {
  YAML::Node msg;
  msg["basic_types_value"] = basic_types_node();
  YAML::Emitter emitter;
  emitter << msg;
  auto generic_msg = yaml_to_rosmsg(emitter.c_str(), "test_msgs", "Nested");

  test_msgs__msg__Nested ros_msg{{
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
  }};

  test_msgs__msg__Nested* converted =
    reinterpret_cast<test_msgs__msg__Nested*>(generic_msg.data);

  EXPECT_EQ(converted->basic_types_value.bool_value, ros_msg.basic_types_value.bool_value);
  EXPECT_EQ(converted->basic_types_value.byte_value, ros_msg.basic_types_value.byte_value);
  EXPECT_EQ(converted->basic_types_value.char_value, ros_msg.basic_types_value.char_value);
  EXPECT_EQ(converted->basic_types_value.float32_value, ros_msg.basic_types_value.float32_value);
  EXPECT_EQ(converted->basic_types_value.float64_value, ros_msg.basic_types_value.float64_value);
  EXPECT_EQ(converted->basic_types_value.int8_value, ros_msg.basic_types_value.int8_value);
  EXPECT_EQ(converted->basic_types_value.uint8_value, ros_msg.basic_types_value.uint8_value);
  EXPECT_EQ(converted->basic_types_value.int16_value, ros_msg.basic_types_value.int16_value);
  EXPECT_EQ(converted->basic_types_value.uint16_value, ros_msg.basic_types_value.uint16_value);
  EXPECT_EQ(converted->basic_types_value.int32_value, ros_msg.basic_types_value.int32_value);
  EXPECT_EQ(converted->basic_types_value.uint32_value, ros_msg.basic_types_value.uint32_value);
  EXPECT_EQ(converted->basic_types_value.int64_value, ros_msg.basic_types_value.int64_value);
  EXPECT_EQ(converted->basic_types_value.uint64_value, ros_msg.basic_types_value.uint64_value);

  ros_message_destroy(&generic_msg);
}

TEST(MsgParser, Arrays) {
  YAML::Node msg;
  msg["bool_values"] = std::vector<bool>{true, true, false};
  msg["byte_values"] = std::vector<uint8_t>{1 ,2 ,3};
  msg["char_values"] = std::vector<uint8_t>{1, 2, 3};
  msg["float32_values"] = std::vector<float>{1, 2, 3};
  msg["float64_values"] = std::vector<double>{10, 20, 30};
  msg["int8_values"] = std::vector<int8_t>{1, 2, 3};
  msg["uint8_values"] = std::vector<uint8_t>{4, 5, 6};
  msg["int16_values"] = std::vector<int16_t>{10, 20, 30};
  msg["uint16_values"] = std::vector<uint16_t>{40, 50, 60};
  msg["int32_values"] = std::vector<int32_t>{100, 200, 300};
  msg["uint32_values"] = std::vector<uint32_t>{400, 500, 600};
  msg["int64_values"] = std::vector<int64_t>{1000, 2000, 3000};
  msg["uint64_values"] = std::vector<uint64_t>{4000, 5000, 6000};
  msg["string_values"] = std::vector<std::string>{"hello", "world", "!"};
  msg["basic_types_values"] = std::vector<YAML::Node>{basic_types_node(), basic_types_node(), basic_types_node()};
  YAML::Emitter emitter;
  emitter << msg;
  auto generic_msg = yaml_to_rosmsg(emitter.c_str(), "test_msgs", "Arrays");

  test_msgs__msg__Arrays* ros_msg = test_msgs__msg__Arrays__create();
  ros_msg->bool_values[0] = true;
  ros_msg->bool_values[1] = true;
  ros_msg->bool_values[2] = false;
  ros_msg->byte_values[0] = 1;
  ros_msg->byte_values[1] = 2;
  ros_msg->byte_values[2] = 3;
  ros_msg->char_values[0] = 1;
  ros_msg->char_values[1] = 2;
  ros_msg->char_values[2] = 3;
  ros_msg->float32_values[0] = 1;
  ros_msg->float32_values[1] = 2;
  ros_msg->float32_values[2] = 3;
  ros_msg->float64_values[0] = 10;
  ros_msg->float64_values[1] = 20;
  ros_msg->float64_values[2] = 30;
  ros_msg->int8_values[0] = 1;
  ros_msg->int8_values[1] = 2;
  ros_msg->int8_values[2] = 3;
  ros_msg->uint8_values[0] = 4;
  ros_msg->uint8_values[1] = 5;
  ros_msg->uint8_values[2] = 6;
  ros_msg->int16_values[0] = 10;
  ros_msg->int16_values[1] = 20;
  ros_msg->int16_values[2] = 30;
  ros_msg->uint16_values[0] = 40;
  ros_msg->uint16_values[1] = 50;
  ros_msg->uint16_values[2] = 60;
  ros_msg->int32_values[0] = 100;
  ros_msg->int32_values[1] = 200;
  ros_msg->int32_values[2] = 300;
  ros_msg->uint32_values[0] = 400;
  ros_msg->uint32_values[1] = 500;
  ros_msg->uint32_values[2] = 600;
  ros_msg->int64_values[0] = 1000;
  ros_msg->int64_values[1] = 2000;
  ros_msg->int64_values[2] = 3000;
  ros_msg->uint64_values[0] = 4000;
  ros_msg->uint64_values[1] = 5000;
  ros_msg->uint64_values[2] = 6000;
  set_basic_types(ros_msg->basic_types_values[0]);
  set_basic_types(ros_msg->basic_types_values[1]);
  set_basic_types(ros_msg->basic_types_values[2]);
  std::vector<std::string> strings{"hello", "world", "!"};
  ros_msg->string_values[0].data = new char[strings[0].size() + 1];
  strcpy(ros_msg->string_values[0].data, strings[0].data());
  ros_msg->string_values[0].size = strings[0].size();
  ros_msg->string_values[0].capacity = strings[0].size() + 1;
  ros_msg->string_values[1].data = new char[strings[1].size() + 1];
  strcpy(ros_msg->string_values[1].data, strings[1].data());
  ros_msg->string_values[1].size = strings[1].size();
  ros_msg->string_values[1].capacity = strings[1].size() + 1;
  ros_msg->string_values[2].data = new char[strings[2].size() + 1];
  strcpy(ros_msg->string_values[2].data, strings[2].data());
  ros_msg->string_values[2].size = strings[2].size();
  ros_msg->string_values[2].capacity = strings[2].size() + 1;

  test_msgs__msg__Arrays* converted =
    reinterpret_cast<test_msgs__msg__Arrays*>(generic_msg.data);

  for (size_t i = 0; i < 3; i++) {
    EXPECT_EQ(converted->bool_values[i], ros_msg->bool_values[i]);
    EXPECT_EQ(converted->byte_values[i], ros_msg->byte_values[i]);
    EXPECT_EQ(converted->char_values[i], ros_msg->char_values[i]);
    EXPECT_EQ(converted->float32_values[i], ros_msg->float32_values[i]);
    EXPECT_EQ(converted->float64_values[i], ros_msg->float64_values[i]);
    EXPECT_EQ(converted->int8_values[i], ros_msg->int8_values[i]);
    EXPECT_EQ(converted->uint8_values[i], ros_msg->uint8_values[i]);
    EXPECT_EQ(converted->int16_values[i], ros_msg->int16_values[i]);
    EXPECT_EQ(converted->uint16_values[i], ros_msg->uint16_values[i]);
    EXPECT_EQ(converted->int32_values[i], ros_msg->int32_values[i]);
    EXPECT_EQ(converted->uint32_values[i], ros_msg->uint32_values[i]);
    EXPECT_EQ(converted->int64_values[i], ros_msg->int64_values[i]);
    EXPECT_EQ(converted->uint64_values[i], ros_msg->uint64_values[i]);
    EXPECT_STREQ(converted->string_values[i].data, ros_msg->string_values[i].data);
    check_basic_types_values(&converted->basic_types_values[i], &ros_msg->basic_types_values[i]);
    EXPECT_EQ(converted->bool_values_default[i], ros_msg->bool_values_default[i]);
    EXPECT_EQ(converted->byte_values_default[i], ros_msg->byte_values_default[i]);
    EXPECT_EQ(converted->char_values_default[i], ros_msg->char_values_default[i]);
    EXPECT_EQ(converted->float32_values_default[i], ros_msg->float32_values_default[i]);
    EXPECT_EQ(converted->float64_values_default[i], ros_msg->float64_values_default[i]);
    EXPECT_EQ(converted->int8_values_default[i], ros_msg->int8_values_default[i]);
    EXPECT_EQ(converted->uint8_values_default[i], ros_msg->uint8_values_default[i]);
    EXPECT_EQ(converted->int16_values_default[i], ros_msg->int16_values_default[i]);
    EXPECT_EQ(converted->uint16_values_default[i], ros_msg->uint16_values_default[i]);
    EXPECT_EQ(converted->int32_values_default[i], ros_msg->int32_values_default[i]);
    EXPECT_EQ(converted->uint32_values_default[i], ros_msg->uint32_values_default[i]);
    EXPECT_EQ(converted->int64_values_default[i], ros_msg->int64_values_default[i]);
    EXPECT_EQ(converted->uint64_values_default[i], ros_msg->uint64_values_default[i]);
    EXPECT_STREQ(converted->string_values_default[i].data, ros_msg->string_values_default[i].data);
  }

  test_msgs__msg__Arrays__destroy(ros_msg);
  ros_message_destroy(&generic_msg);
}
