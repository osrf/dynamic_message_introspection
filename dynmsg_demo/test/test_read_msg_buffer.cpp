#include "../src/message_reading.hpp"
#include "../src/typesupport_utils.hpp"

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
#include <test_msgs/msg/bounded_sequences.h>
#include <test_msgs/msg/unbounded_sequences.h>
#include <test_msgs/msg/multi_nested.h>
#include <test_msgs/msg/strings.h>
#include <test_msgs/msg/w_strings.h>

#include <rosidl_runtime_c/primitives_sequence_functions.h>
#include <rosidl_runtime_c/string_functions.h>
#include <rosidl_runtime_c/u16string_functions.h>

#include <gtest/gtest.h>
#include <limits>


void FillInPose(geometry_msgs__msg__Pose &pose, double offset)
{
  pose.position.x = offset;
  pose.position.y = offset + 1;
  pose.position.z = offset + 2;
  pose.orientation.x = offset + 3;
  pose.orientation.y = offset + 4;
  pose.orientation.z = offset + 5;
  pose.orientation.w = offset + 6;
}


dynmsg_msgs__msg__ComplexMsg* MakeMegaMessage()
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
  geometry_msgs__msg__Pose__init(&msg->a_pose);
  FillInPose(msg->a_pose, 0);

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
  rosidl_runtime_c__String__assign(&msg->a_string_array[0], "one");
  rosidl_runtime_c__String__assign(&msg->a_string_array[1], "two");
  rosidl_runtime_c__String__assign(&msg->a_string_array[2], "three");
  rosidl_runtime_c__String__assign(&msg->a_string_array[3], "four");
  rosidl_runtime_c__String__assign(&msg->a_string_array[4], "five");
  //msg->a_wstring_array = ;
  for (int ii = 0; ii < 5; ++ii) {
    FillInPose(msg->a_pose_array[ii], ii);
  }

  rosidl_runtime_c__boolean__Sequence__init(
    &msg->a_bounded_bool_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_bool_array__MAX_SIZE);
  msg->a_bounded_bool_array.data[0] = true;
  msg->a_bounded_bool_array.data[1] = false;
  msg->a_bounded_bool_array.data[2] = true;
  msg->a_bounded_bool_array.data[3] = true;
  msg->a_bounded_bool_array.data[4] = false;
  msg->a_bounded_bool_array.data[5] = true;
  msg->a_bounded_bool_array.data[6] = false;
  msg->a_bounded_bool_array.data[7] = true;
  msg->a_bounded_bool_array.data[8] = true;
  msg->a_bounded_bool_array.data[9] = false;
  rosidl_runtime_c__byte__Sequence__init(
    &msg->a_bounded_byte_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_byte_array__MAX_SIZE);
  msg->a_bounded_byte_array.data[0] = 0x10;
  msg->a_bounded_byte_array.data[1] = 0x20;
  msg->a_bounded_byte_array.data[2] = 0x30;
  msg->a_bounded_byte_array.data[3] = 0x40;
  msg->a_bounded_byte_array.data[4] = 0x50;
  msg->a_bounded_byte_array.data[5] = 0x60;
  msg->a_bounded_byte_array.data[6] = 0x70;
  msg->a_bounded_byte_array.data[7] = 0x80;
  msg->a_bounded_byte_array.data[8] = 0x90;
  msg->a_bounded_byte_array.data[9] = 0xA0;
  rosidl_runtime_c__uint8__Sequence__init(
    &msg->a_bounded_char_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_char_array__MAX_SIZE);
  msg->a_bounded_char_array.data[0] = 'a';
  msg->a_bounded_char_array.data[1] = 'b';
  msg->a_bounded_char_array.data[2] = 'c';
  msg->a_bounded_char_array.data[3] = 'd';
  msg->a_bounded_char_array.data[4] = 'e';
  msg->a_bounded_char_array.data[5] = 'f';
  msg->a_bounded_char_array.data[6] = 'g';
  msg->a_bounded_char_array.data[7] = 'h';
  msg->a_bounded_char_array.data[8] = 'i';
  msg->a_bounded_char_array.data[9] = 'j';
  rosidl_runtime_c__float__Sequence__init(
    &msg->a_bounded_float_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_float_array__MAX_SIZE);
  msg->a_bounded_float_array.data[0] = std::numeric_limits<float>::min();
  msg->a_bounded_float_array.data[1] = std::numeric_limits<float>::lowest();
  msg->a_bounded_float_array.data[2] = std::numeric_limits<float>::epsilon();
  msg->a_bounded_float_array.data[3] = std::numeric_limits<float>::max();
  msg->a_bounded_float_array.data[4] = std::numeric_limits<float>::round_error();
  msg->a_bounded_float_array.data[5] = std::numeric_limits<float>::min();
  msg->a_bounded_float_array.data[6] = std::numeric_limits<float>::lowest();
  msg->a_bounded_float_array.data[7] = std::numeric_limits<float>::epsilon();
  msg->a_bounded_float_array.data[8] = std::numeric_limits<float>::max();
  msg->a_bounded_float_array.data[9] = std::numeric_limits<float>::round_error();
  rosidl_runtime_c__double__Sequence__init(
    &msg->a_bounded_double_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_double_array__MAX_SIZE);
  msg->a_bounded_double_array.data[0] = std::numeric_limits<double>::min();
  msg->a_bounded_double_array.data[1] = std::numeric_limits<double>::lowest();
  msg->a_bounded_double_array.data[2] = std::numeric_limits<double>::epsilon();
  msg->a_bounded_double_array.data[3] = std::numeric_limits<double>::max();
  msg->a_bounded_double_array.data[4] = std::numeric_limits<double>::round_error();
  msg->a_bounded_double_array.data[5] = std::numeric_limits<double>::min();
  msg->a_bounded_double_array.data[6] = std::numeric_limits<double>::lowest();
  msg->a_bounded_double_array.data[7] = std::numeric_limits<double>::epsilon();
  msg->a_bounded_double_array.data[8] = std::numeric_limits<double>::max();
  msg->a_bounded_double_array.data[9] = std::numeric_limits<double>::round_error();
  rosidl_runtime_c__int8__Sequence__init(
    &msg->a_bounded_int8_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_int8_array__MAX_SIZE);
  msg->a_bounded_int8_array.data[0] = std::numeric_limits<int8_t>::min();
  msg->a_bounded_int8_array.data[1] = std::numeric_limits<int8_t>::lowest();
  msg->a_bounded_int8_array.data[2] = 0;
  msg->a_bounded_int8_array.data[3] = std::numeric_limits<int8_t>::max() / 5;
  msg->a_bounded_int8_array.data[4] = std::numeric_limits<int8_t>::max();
  msg->a_bounded_int8_array.data[5] = std::numeric_limits<int8_t>::min();
  msg->a_bounded_int8_array.data[6] = std::numeric_limits<int8_t>::lowest();
  msg->a_bounded_int8_array.data[7] = 0;
  msg->a_bounded_int8_array.data[8] = std::numeric_limits<int8_t>::max() / 5;
  msg->a_bounded_int8_array.data[9] = std::numeric_limits<int8_t>::max();
  rosidl_runtime_c__uint8__Sequence__init(
    &msg->a_bounded_uint8_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_uint8_array__MAX_SIZE);
  msg->a_bounded_uint8_array.data[0] = std::numeric_limits<uint8_t>::min();
  msg->a_bounded_uint8_array.data[1] = std::numeric_limits<uint8_t>::lowest();
  msg->a_bounded_uint8_array.data[2] = 0;
  msg->a_bounded_uint8_array.data[3] = std::numeric_limits<uint8_t>::max() / 5;
  msg->a_bounded_uint8_array.data[4] = std::numeric_limits<uint8_t>::max();
  msg->a_bounded_uint8_array.data[5] = std::numeric_limits<uint8_t>::min();
  msg->a_bounded_uint8_array.data[6] = std::numeric_limits<uint8_t>::lowest();
  msg->a_bounded_uint8_array.data[7] = 0;
  msg->a_bounded_uint8_array.data[8] = std::numeric_limits<uint8_t>::max() / 5;
  msg->a_bounded_uint8_array.data[9] = std::numeric_limits<uint8_t>::max();
  rosidl_runtime_c__int16__Sequence__init(
    &msg->a_bounded_int16_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_int16_array__MAX_SIZE);
  msg->a_bounded_int16_array.data[0] = std::numeric_limits<int16_t>::min();
  msg->a_bounded_int16_array.data[1] = std::numeric_limits<int16_t>::lowest();
  msg->a_bounded_int16_array.data[2] = 0;
  msg->a_bounded_int16_array.data[3] = std::numeric_limits<int16_t>::max() / 5;
  msg->a_bounded_int16_array.data[4] = std::numeric_limits<int16_t>::max();
  msg->a_bounded_int16_array.data[5] = std::numeric_limits<int16_t>::min();
  msg->a_bounded_int16_array.data[6] = std::numeric_limits<int16_t>::lowest();
  msg->a_bounded_int16_array.data[7] = 0;
  msg->a_bounded_int16_array.data[8] = std::numeric_limits<int16_t>::max() / 5;
  msg->a_bounded_int16_array.data[9] = std::numeric_limits<int16_t>::max();
  rosidl_runtime_c__uint16__Sequence__init(
    &msg->a_bounded_uint16_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_uint16_array__MAX_SIZE);
  msg->a_bounded_uint16_array.data[0] = std::numeric_limits<uint16_t>::min();
  msg->a_bounded_uint16_array.data[1] = std::numeric_limits<uint16_t>::lowest();
  msg->a_bounded_uint16_array.data[2] = 0;
  msg->a_bounded_uint16_array.data[3] = std::numeric_limits<uint16_t>::max() / 5;
  msg->a_bounded_uint16_array.data[4] = std::numeric_limits<uint16_t>::max();
  msg->a_bounded_uint16_array.data[5] = std::numeric_limits<uint16_t>::min();
  msg->a_bounded_uint16_array.data[6] = std::numeric_limits<uint16_t>::lowest();
  msg->a_bounded_uint16_array.data[7] = 0;
  msg->a_bounded_uint16_array.data[8] = std::numeric_limits<uint16_t>::max() / 5;
  msg->a_bounded_uint16_array.data[9] = std::numeric_limits<uint16_t>::max();
  rosidl_runtime_c__int32__Sequence__init(
    &msg->a_bounded_int32_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_int32_array__MAX_SIZE);
  msg->a_bounded_int32_array.data[0] = std::numeric_limits<int32_t>::min();
  msg->a_bounded_int32_array.data[1] = std::numeric_limits<int32_t>::lowest();
  msg->a_bounded_int32_array.data[2] = 0;
  msg->a_bounded_int32_array.data[3] = std::numeric_limits<int32_t>::max() / 5;
  msg->a_bounded_int32_array.data[4] = std::numeric_limits<int32_t>::max();
  msg->a_bounded_int32_array.data[5] = std::numeric_limits<int32_t>::min();
  msg->a_bounded_int32_array.data[6] = std::numeric_limits<int32_t>::lowest();
  msg->a_bounded_int32_array.data[7] = 0;
  msg->a_bounded_int32_array.data[8] = std::numeric_limits<int32_t>::max() / 5;
  msg->a_bounded_int32_array.data[9] = std::numeric_limits<int32_t>::max();
  rosidl_runtime_c__uint32__Sequence__init(
    &msg->a_bounded_uint32_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_uint32_array__MAX_SIZE);
  msg->a_bounded_uint32_array.data[0] = std::numeric_limits<uint32_t>::min();
  msg->a_bounded_uint32_array.data[1] = std::numeric_limits<uint32_t>::lowest();
  msg->a_bounded_uint32_array.data[2] = 0;
  msg->a_bounded_uint32_array.data[3] = std::numeric_limits<uint32_t>::max() / 5;
  msg->a_bounded_uint32_array.data[4] = std::numeric_limits<uint32_t>::max();
  msg->a_bounded_uint32_array.data[5] = std::numeric_limits<uint32_t>::min();
  msg->a_bounded_uint32_array.data[6] = std::numeric_limits<uint32_t>::lowest();
  msg->a_bounded_uint32_array.data[7] = 0;
  msg->a_bounded_uint32_array.data[8] = std::numeric_limits<uint32_t>::max() / 5;
  msg->a_bounded_uint32_array.data[9] = std::numeric_limits<uint32_t>::max();
  rosidl_runtime_c__int64__Sequence__init(
    &msg->a_bounded_int64_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_int64_array__MAX_SIZE);
  msg->a_bounded_int64_array.data[0] = std::numeric_limits<int64_t>::min();
  msg->a_bounded_int64_array.data[1] = std::numeric_limits<int64_t>::lowest();
  msg->a_bounded_int64_array.data[2] = 0;
  msg->a_bounded_int64_array.data[3] = std::numeric_limits<int64_t>::max() / 5;
  msg->a_bounded_int64_array.data[4] = std::numeric_limits<int64_t>::max();
  msg->a_bounded_int64_array.data[5] = std::numeric_limits<int64_t>::min();
  msg->a_bounded_int64_array.data[6] = std::numeric_limits<int64_t>::lowest();
  msg->a_bounded_int64_array.data[7] = 0;
  msg->a_bounded_int64_array.data[8] = std::numeric_limits<int64_t>::max() / 5;
  msg->a_bounded_int64_array.data[9] = std::numeric_limits<int64_t>::max();
  rosidl_runtime_c__uint64__Sequence__init(
    &msg->a_bounded_uint64_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_uint64_array__MAX_SIZE);
  msg->a_bounded_uint64_array.data[0] = std::numeric_limits<uint64_t>::min();
  msg->a_bounded_uint64_array.data[1] = std::numeric_limits<uint64_t>::lowest();
  msg->a_bounded_uint64_array.data[2] = 0;
  msg->a_bounded_uint64_array.data[3] = std::numeric_limits<uint64_t>::max() / 5;
  msg->a_bounded_uint64_array.data[4] = std::numeric_limits<uint64_t>::max();
  msg->a_bounded_uint64_array.data[5] = std::numeric_limits<uint64_t>::min();
  msg->a_bounded_uint64_array.data[6] = std::numeric_limits<uint64_t>::lowest();
  msg->a_bounded_uint64_array.data[7] = 0;
  msg->a_bounded_uint64_array.data[8] = std::numeric_limits<uint64_t>::max() / 5;
  msg->a_bounded_uint64_array.data[9] = std::numeric_limits<uint64_t>::max();
  //msg->a_bounded_string_array;
  rosidl_runtime_c__String__Sequence__init(
    &msg->a_bounded_string_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_string_array__MAX_SIZE);
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[0], "one");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[1], "two");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[2], "three");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[3], "four");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[4], "five");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[5], "six");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[6], "seven");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[7], "eight");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[8], "nine");
  rosidl_runtime_c__String__assign(&msg->a_bounded_string_array.data[9], "ten");
  //msg->a_bounded_wstring_array;
  geometry_msgs__msg__Pose__Sequence__init(
    &msg->a_bounded_pose_array,
    dynmsg_msgs__msg__ComplexMsg__a_bounded_pose_array__MAX_SIZE);
  for (int ii = 0; ii < dynmsg_msgs__msg__ComplexMsg__a_bounded_pose_array__MAX_SIZE; ++ii) {
    FillInPose(msg->a_bounded_pose_array.data[ii], ii * 10);
  }

  rosidl_runtime_c__boolean__Sequence__init(
    &msg->an_unbounded_bool_array,
    3);
  msg->an_unbounded_bool_array.data[0] = true;
  msg->an_unbounded_bool_array.data[1] = false;
  msg->an_unbounded_bool_array.data[2] = true;
  rosidl_runtime_c__byte__Sequence__init(
    &msg->an_unbounded_byte_array,
    3);
  msg->an_unbounded_byte_array.data[0] = 0x10;
  msg->an_unbounded_byte_array.data[1] = 0x20;
  msg->an_unbounded_byte_array.data[2] = 0x30;
  rosidl_runtime_c__uint8__Sequence__init(
    &msg->an_unbounded_char_array,
    3);
  msg->an_unbounded_char_array.data[0] = 'a';
  msg->an_unbounded_char_array.data[1] = 'b';
  msg->an_unbounded_char_array.data[2] = 'c';
  rosidl_runtime_c__float__Sequence__init(
    &msg->an_unbounded_float_array,
    3);
  msg->an_unbounded_float_array.data[0] = std::numeric_limits<float>::min();
  msg->an_unbounded_float_array.data[1] = std::numeric_limits<float>::lowest();
  msg->an_unbounded_float_array.data[2] = std::numeric_limits<float>::epsilon();
  rosidl_runtime_c__double__Sequence__init(
    &msg->an_unbounded_double_array,
    3);
  msg->an_unbounded_double_array.data[0] = std::numeric_limits<double>::min();
  msg->an_unbounded_double_array.data[1] = std::numeric_limits<double>::lowest();
  msg->an_unbounded_double_array.data[2] = std::numeric_limits<double>::epsilon();
  rosidl_runtime_c__int8__Sequence__init(
    &msg->an_unbounded_int8_array,
    3);
  msg->an_unbounded_int8_array.data[0] = std::numeric_limits<int8_t>::min();
  msg->an_unbounded_int8_array.data[1] = std::numeric_limits<int8_t>::lowest();
  msg->an_unbounded_int8_array.data[2] = 0;
  rosidl_runtime_c__uint8__Sequence__init(
    &msg->an_unbounded_uint8_array,
    3);
  msg->an_unbounded_uint8_array.data[0] = std::numeric_limits<uint8_t>::min();
  msg->an_unbounded_uint8_array.data[1] = std::numeric_limits<uint8_t>::lowest();
  msg->an_unbounded_uint8_array.data[2] = 0;
  rosidl_runtime_c__int16__Sequence__init(
    &msg->an_unbounded_int16_array,
    3);
  msg->an_unbounded_int16_array.data[0] = std::numeric_limits<int16_t>::min();
  msg->an_unbounded_int16_array.data[1] = std::numeric_limits<int16_t>::lowest();
  msg->an_unbounded_int16_array.data[2] = 0;
  rosidl_runtime_c__uint16__Sequence__init(
    &msg->an_unbounded_uint16_array,
    3);
  msg->an_unbounded_uint16_array.data[0] = std::numeric_limits<uint16_t>::min();
  msg->an_unbounded_uint16_array.data[1] = std::numeric_limits<uint16_t>::lowest();
  msg->an_unbounded_uint16_array.data[2] = 0;
  rosidl_runtime_c__int32__Sequence__init(
    &msg->an_unbounded_int32_array,
    3);
  msg->an_unbounded_int32_array.data[0] = std::numeric_limits<int32_t>::min();
  msg->an_unbounded_int32_array.data[1] = std::numeric_limits<int32_t>::lowest();
  msg->an_unbounded_int32_array.data[2] = 0;
  rosidl_runtime_c__uint32__Sequence__init(
    &msg->an_unbounded_uint32_array,
    3);
  msg->an_unbounded_uint32_array.data[0] = std::numeric_limits<uint32_t>::min();
  msg->an_unbounded_uint32_array.data[1] = std::numeric_limits<uint32_t>::lowest();
  msg->an_unbounded_uint32_array.data[2] = 0;
  rosidl_runtime_c__int64__Sequence__init(
    &msg->an_unbounded_int64_array,
    3);
  msg->an_unbounded_int64_array.data[0] = std::numeric_limits<int64_t>::min();
  msg->an_unbounded_int64_array.data[1] = std::numeric_limits<int64_t>::lowest();
  msg->an_unbounded_int64_array.data[2] = 0;
  rosidl_runtime_c__uint64__Sequence__init(
    &msg->an_unbounded_uint64_array,
    3);
  msg->an_unbounded_uint64_array.data[0] = std::numeric_limits<uint64_t>::min();
  msg->an_unbounded_uint64_array.data[1] = std::numeric_limits<uint64_t>::lowest();
  msg->an_unbounded_uint64_array.data[2] = 0;
  //msg->a_bounded_string_array;
  rosidl_runtime_c__String__Sequence__init(
    &msg->an_unbounded_string_array,
    3);
  rosidl_runtime_c__String__assign(&msg->an_unbounded_string_array.data[0], "one");
  rosidl_runtime_c__String__assign(&msg->an_unbounded_string_array.data[1], "two");
  rosidl_runtime_c__String__assign(&msg->an_unbounded_string_array.data[2], "three");
  //msg->a_bounded_wstring_array;
  geometry_msgs__msg__Pose__Sequence__init(&msg->an_unbounded_pose_array, 3);
  for (int ii = 0; ii < 3; ++ii) {
    FillInPose(msg->an_unbounded_pose_array.data[ii], ii * 100);
  }

  return msg;
}

TEST(ReadMsgBuffer, ReadWholeMessage)
{
  auto * msg = MakeMegaMessage();
  RosMessage message;
  message.type_info = get_type_info("dynmsg_msgs", "ComplexMsg");
  message.data = reinterpret_cast<uint8_t *>(msg);

  std::stringstream output;
  //message_to_string(message, 1, output);
}

TEST(ReadMsgBuffer, ReadBool)
{
  example_interfaces__msg__Bool * msg = example_interfaces__msg__Bool__create();
  msg->data = true;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Bool");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (boolean):\t1\n");

  example_interfaces__msg__Bool__fini(msg);
}

TEST(ReadMsgBuffer, ReadByte)
{
  example_interfaces__msg__Byte * msg = example_interfaces__msg__Byte__create();
  msg->data = 0x42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Byte");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (octet):\t0x42\n");

  example_interfaces__msg__Byte__fini(msg);
}

TEST(ReadMsgBuffer, ReadChar)
{
  example_interfaces__msg__Char * msg = example_interfaces__msg__Char__create();
  msg->data = 'a';

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Char");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (uint8):\t97\n");

  example_interfaces__msg__Char__fini(msg);
}

TEST(ReadMsgBuffer, ReadFloat32)
{
  example_interfaces__msg__Float32 * msg = example_interfaces__msg__Float32__create();
  msg->data = 42.42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Float32");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (float):\t42.42\n");

  example_interfaces__msg__Float32__fini(msg);
}

TEST(ReadMsgBuffer, ReadFloat64)
{
  example_interfaces__msg__Float64 * msg = example_interfaces__msg__Float64__create();
  msg->data = 42424242424242.42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Float64");
  message.data = reinterpret_cast<uint8_t *>(msg);
  output << std::fixed << std::setprecision(2);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (double):\t42424242424242.42\n");

  output << std::defaultfloat << std::setprecision(6);
  example_interfaces__msg__Float64__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt8)
{
  example_interfaces__msg__Int8 * msg = example_interfaces__msg__Int8__create();
  msg->data = -42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Int8");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (int8):\t-42\n");

  example_interfaces__msg__Int8__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt8)
{
  example_interfaces__msg__UInt8 * msg = example_interfaces__msg__UInt8__create();
  msg->data = 142;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "UInt8");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (uint8):\t142\n");

  example_interfaces__msg__UInt8__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt16)
{
  example_interfaces__msg__Int16 * msg = example_interfaces__msg__Int16__create();
  msg->data = -4242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Int16");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (int16):\t-4242\n");

  example_interfaces__msg__Int16__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt16)
{
  example_interfaces__msg__UInt16 * msg = example_interfaces__msg__UInt16__create();
  msg->data = 4242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "UInt16");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (uint16):\t4242\n");

  example_interfaces__msg__UInt16__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt32)
{
  example_interfaces__msg__Int32 * msg = example_interfaces__msg__Int32__create();
  msg->data = -42424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Int32");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (int32):\t-42424242\n");

  example_interfaces__msg__Int32__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt32)
{
  example_interfaces__msg__UInt32 * msg = example_interfaces__msg__UInt32__create();
  msg->data = 4242424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "UInt32");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (uint32):\t4242424242\n");

  example_interfaces__msg__UInt32__fini(msg);
}

TEST(ReadMsgBuffer, ReadInt64)
{
  example_interfaces__msg__Int64 * msg = example_interfaces__msg__Int64__create();
  msg->data = -424242424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "Int64");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (int64):\t-424242424242\n");

  example_interfaces__msg__Int64__fini(msg);
}

TEST(ReadMsgBuffer, ReadUInt64)
{
  example_interfaces__msg__UInt64 * msg = example_interfaces__msg__UInt64__create();
  msg->data = 424242424242;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("example_interfaces", "UInt64");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (uint64):\t424242424242\n");

  example_interfaces__msg__UInt64__fini(msg);
}

void populate_basic_types(test_interface_files__msg__BasicTypes * msg)
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

TEST(ReadMsgBuffer, ReadArrays)
{
  test_interface_files__msg__Arrays * msg = test_interface_files__msg__Arrays__create();
  msg->bool_values[0] = true; msg->bool_values[1] = false; msg->bool_values[2] = true;
  msg->byte_values[0] = std::numeric_limits<uint8_t>::min();
  msg->byte_values[1] = 0
  msg->byte_values[2] = std::numeric_limits<uint8_t>::max();
  msg->char_values[0] = std::numeric_limits<char>::min();
  msg->char_values[1] = 0
  msg->char_values[2] = std::numeric_limits<char>::max();
  msg->float32_values[0] = std::numeric_limits<float>::min();
  msg->float32_values[1] = std::numeric_limits<float>::epsilon();
  msg->float32_values[2] = std::numeric_limits<float>::max();
  msg->float64_values[0] = std::numeric_limits<double>::min();
  msg->float64_values[1] = std::numeric_limits<double>::epsilon();
  msg->float64_values[2] = std::numeric_limits<double>::max();
  msg->int8_values[0] = std::numeric_limits<int8_t>::min();
  msg->int8_values[1] = 0
  msg->int8_values[2] = std::numeric_limits<int8_t>::max();
  msg->uint8_values[0] = std::numeric_limits<uint8_t>::min();
  msg->uint8_values[1] = 0
  msg->uint8_values[2] = std::numeric_limits<uint8_t>::max();
  msg->int16_values[0] = std::numeric_limits<int16_t>::min();
  msg->int16_values[1] = 0
  msg->int16_values[2] = std::numeric_limits<int16_t>::max();
  msg->uint16_values[0] = std::numeric_limits<uint16_t>::min();
  msg->uint16_values[1] = 0
  msg->uint16_values[2] = std::numeric_limits<uint16_t>::max();
  msg->int32_values[0] = std::numeric_limits<int32_t>::min();
  msg->int32_values[1] = 0
  msg->int32_values[2] = std::numeric_limits<int32_t>::max();
  msg->uint32_values[0] = std::numeric_limits<uint32_t>::min();
  msg->uint32_values[1] = 0
  msg->uint32_values[2] = std::numeric_limits<uint32_t>::max();
  msg->int64_values[0] = std::numeric_limits<int64_t>::min();
  msg->int64_values[1] = 0
  msg->int64_values[2] = std::numeric_limits<int64_t>::max();
  msg->uint64_values[0] = std::numeric_limits<uint64_t>::min();
  msg->uint64_values[1] = 0
  msg->uint64_values[2] = std::numeric_limits<uint64_t>::max();
  rosidl_runtime_c__String__assign(&msg->string_values[0], "one");
  rosidl_runtime_c__String__assign(&msg->string_values[1], "two");
  rosidl_runtime_c__String__assign(&msg->string_values[2], "three");
  for (int ii = 0; ii < 3; ++ii) {
    populate_basic_types(msg->basic_types_values[ii];
  }
  msg->alignment_check = 42;

  std::stringstream output;
  RosMessage message;
  message.type_info = get_type_info("test_interface_files", "Arrays");
  message.data = reinterpret_cast<uint8_t *>(msg);
  message_to_string(message, 1, output);

  EXPECT_EQ(output.str(), "  data (int32):\t-42424242\n");

  test_interface_files__msg__Arrays__fini(msg);
}
