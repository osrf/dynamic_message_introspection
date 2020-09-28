#include "../src/msg_parser.hpp"
#include "../src/typesupport_utils.hpp"

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>

#include <iomanip>
#include <sstream>

#include <gtest/gtest.h>

std::string sprint_bytes(const void* data, size_t size) {
  std::vector<char> buffer(size * 3);
  for (size_t i = 0; i < size; i++) {
    sprintf(buffer.data() + i * 3, "%02X", ((uint8_t*) data)[i]);
    buffer[i * 3 + 2] = ' ';
  }
  return std::string(buffer.begin(), buffer.end());
}

TEST(MsgParser, Int32) {
  auto* typeinfo = get_type_info("std_msgs", "Int32");
  auto buffer = yaml_to_rosmsg("{ data: 123 }", typeinfo);

  std_msgs__msg__Int32 ros_msg{
    data: 123,
  };

  EXPECT_EQ(memcmp(buffer.data(), &ros_msg, sizeof(ros_msg)), 0)
    << "got: " << sprint_bytes(buffer.data(), buffer.size()) << std::endl
    << "expect: " << sprint_bytes(&ros_msg, sizeof(ros_msg)) << std::endl;
}

TEST(MsgParser, String) {
  auto* typeinfo = get_type_info("std_msgs", "String");
  auto buffer = yaml_to_rosmsg("{ data: hello }", typeinfo);

  std_msgs__msg__String ros_msg{
    data: {
      data: "hello",
      size: 5,
      capacity: 6
    },
  };

  rosidl_runtime_c__String* created_msg =
    reinterpret_cast<rosidl_runtime_c__String*>(buffer.data());

  EXPECT_STREQ(created_msg->data, ros_msg.data.data);
}
