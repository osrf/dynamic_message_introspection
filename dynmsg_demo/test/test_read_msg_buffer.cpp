#include <dynmsg_msgs/msg/complex_msg.h>

#include <rosidl_runtime_c/string_functions.h>
#include <rosidl_runtime_c/u16string_functions.h>

#include <gtest/gtest.h>
#include <limits>

const dynmsg_msgs__msg__ComplexMsg* MakeMegaMessage()
{
  dynmsg_msgs__msg__ComplexMsg * msg = dynmsg_msgs__msg__ComplexMsg__create();
  msg->a_bool = true;
  msg->a_byte = 0x42;
  msg->a_char = '*';
  msg->a_float = 42.42;
  msg->a_double = 4242424242.424242;
  msg->an_int8 = -42;
  msg->a_uint8 = 142;
  msg->an_int16 = -4242;
  msg->a_uint16 =  4242;
  msg->an_int32 =  -42424242;
  msg->a_uint32 =  4242424242;
  msg->an_int64 = -424242424242;
  msg->a_uint64 = 424242424242;
  rosidl_runtime_c__String__assign(&(msg->a_string), "forty two");
  //rosidl_runtime_c__U16String__assign(&(msg->a_wstring), u"z\u00df\u6c34\U0001d10b");
  //msg->a_pose = ;
  msg->a_bool_array[0] = true;
  msg->a_bool_array[1] = false;
  msg->a_bool_array[2] = true;
  msg->a_bool_array[3] = true;
  msg->a_bool_array[4] = false;
  msg->a_byte_array[0] = 0x10;
  msg->a_byte_array[1] = 0x20;
  msg->a_byte_array[2] = 0x30;
  msg->a_byte_array[3] = 0x40;
  msg->a_byte_array[4] = 0x50;
  msg->a_char_array[0] = 'a';
  msg->a_char_array[1] = 'b';
  msg->a_char_array[2] = 'c';
  msg->a_char_array[3] = 'd';
  msg->a_char_array[4] = 'e';
  msg->a_float_array[0] = std::numeric_limits<float>::min();
  msg->a_float_array[1] = std::numeric_limits<float>::lowest();
  msg->a_float_array[2] = std::numeric_limits<float>::epsilon();
  msg->a_float_array[3] = std::numeric_limits<float>::max();
  msg->a_float_array[4] = std::numeric_limits<float>::round_error();
  msg->a_double_array[0] = std::numeric_limits<double>::min();
  msg->a_double_array[1] = std::numeric_limits<double>::lowest();
  msg->a_double_array[2] = std::numeric_limits<double>::epsilon();
  msg->a_double_array[3] = std::numeric_limits<double>::max();
  msg->a_double_array[4] = std::numeric_limits<double>::round_error();
  msg->an_int8_array[0] = std::numeric_limits<int8_t>::min();
  msg->an_int8_array[1] = std::numeric_limits<int8_t>::lowest();
  msg->an_int8_array[2] = 0;
  msg->an_int8_array[3] = std::numeric_limits<int8_t>::max() / 5;
  msg->an_int8_array[4] = std::numeric_limits<int8_t>::max();
  msg->a_uint8_array[0] = std::numeric_limits<uint8_t>::min();
  msg->a_uint8_array[1] = std::numeric_limits<uint8_t>::lowest();
  msg->a_uint8_array[2] = 0;
  msg->a_uint8_array[3] = std::numeric_limits<uint8_t>::max() / 5;
  msg->a_uint8_array[4] = std::numeric_limits<uint8_t>::max();
  msg->an_int16_array[0] = std::numeric_limits<int16_t>::min();
  msg->an_int16_array[1] = std::numeric_limits<int16_t>::lowest();
  msg->an_int16_array[2] = 0;
  msg->an_int16_array[3] = std::numeric_limits<int16_t>::max() / 5;
  msg->an_int16_array[4] = std::numeric_limits<int16_t>::max();
  msg->a_uint16_array[0] = std::numeric_limits<uint16_t>::min();
  msg->a_uint16_array[1] = std::numeric_limits<uint16_t>::lowest();
  msg->a_uint16_array[2] = 0;
  msg->a_uint16_array[3] = std::numeric_limits<uint16_t>::max() / 5;
  msg->a_uint16_array[4] = std::numeric_limits<uint16_t>::max();
  msg->an_int32_array[0] = std::numeric_limits<int32_t>::min();
  msg->an_int32_array[1] = std::numeric_limits<int32_t>::lowest();
  msg->an_int32_array[2] = 0;
  msg->an_int32_array[3] = std::numeric_limits<int32_t>::max() / 5;
  msg->an_int32_array[4] = std::numeric_limits<int32_t>::max();
  msg->a_uint32_array[0] = std::numeric_limits<uint32_t>::min();
  msg->a_uint32_array[1] = std::numeric_limits<uint32_t>::lowest();
  msg->a_uint32_array[2] = 0;
  msg->a_uint32_array[3] = std::numeric_limits<uint32_t>::max() / 5;
  msg->a_uint32_array[4] = std::numeric_limits<uint32_t>::max();
  msg->an_int64_array[0] = std::numeric_limits<int64_t>::min();
  msg->an_int64_array[1] = std::numeric_limits<int64_t>::lowest();
  msg->an_int64_array[2] = 0;
  msg->an_int64_array[3] = std::numeric_limits<int64_t>::max() / 5;
  msg->an_int64_array[4] = std::numeric_limits<int64_t>::max();
  msg->a_uint64_array[0] = std::numeric_limits<uint64_t>::min();
  msg->a_uint64_array[1] = std::numeric_limits<uint64_t>::lowest();
  msg->a_uint64_array[2] = 0;
  msg->a_uint64_array[3] = std::numeric_limits<uint64_t>::max() / 5;
  msg->a_uint64_array[4] = std::numeric_limits<uint64_t>::max();
  //msg->a_string_array = ;
  //msg->a_wstring_array = ;
  //msg->a_pose_array = ;
  //msg->a_bounded_bool_array;
  //msg->a_bounded_byte_array;
  //msg->a_bounded_char_array;
  //msg->a_bounded_float_array;
  //msg->a_bounded_double_array;
  //msg->a_bounded_int8_array;
  //msg->a_bounded_uint8_array;
  //msg->a_bounded_int16_array;
  //msg->a_bounded_uint16_array;
  //msg->a_bounded_int32_array;
  //msg->a_bounded_uint32_array;
  //msg->a_bounded_int64_array;
  //msg->a_bounded_uint64_array;
  //msg->a_bounded_string_array;
  //msg->a_bounded_wstring_array;
  //msg->a_bounded_pose_array;
  //msg->an_unbounded_bool_array;
  //msg->an_unbounded_byte_array;
  //msg->an_unbounded_char_array;
  //msg->an_unbounded_float_array;
  //msg->an_unbounded_double_array;
  //msg->an_unbounded_int8_array;
  //msg->an_unbounded_uint8_array;
  //msg->an_unbounded_int16_array;
  //msg->an_unbounded_uint16_array;
  //msg->an_unbounded_int32_array;
  //msg->an_unbounded_uint32_array;
  //msg->an_unbounded_int64_array;
  //msg->an_unbounded_uint64_array;
  //msg->an_unbounded_string_array;
  //msg->an_unbounded_wstring_array;
  //msg->an_unbounded_pose_array;

  return msg;
}

TEST(ReadMsgBuffer, ReadWholeMessage)
{
  auto * msg = MakeMegaMessage();
  EXPECT_EQ(msg->a_bool, true);
}
