#include "cli.hpp"
#include "string_utils.hpp"
#include "typesupport_utils.hpp"

#include <dlfcn.h>
#include <unistd.h>

#include <clocale>
#include <iostream>
#include <locale>
#include <memory>
#include <sstream>
#include <vector>

#include "rcl/context.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/rcl.h"
#include "rcl/subscription.h"
#include "rcl/types.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/u16string.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/field_types.h"

#include "rcutils/logging_macros.h"

void message_to_string(RosMessage &message, size_t indent_level, std::stringstream &output);


const char *
member_type_to_string(const rosidl_typesupport_introspection_c__MessageMember &type_info)
{
  switch (type_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      return "float";
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      return "double";
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      return "long double";
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      return "char";
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      return "wchar";
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      return "boolean";
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      return "octet";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      return "uint8";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      return "int8";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      return "uint16";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      return "int16";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      return "uint32";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      return "int32";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      return "uint64";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      return "int64";
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      return "string";
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      return "wstring";
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      return "message";
    default:
      return "UNKNOWN";
  }
}


size_t
size_of_member_type(uint8_t type_id)
{
  switch (type_id) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      return sizeof(float);
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      return sizeof(double);
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      return sizeof(long double);
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      return sizeof(uint8_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      return sizeof(uint16_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      return sizeof(bool);
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      return sizeof(uint8_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      return sizeof(uint8_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      return sizeof(int8_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      return sizeof(uint16_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      return sizeof(int16_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      return sizeof(uint32_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      return sizeof(int32_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      return sizeof(uint64_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      return sizeof(int64_t);
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      assert(0 && "Cannot get the size of a string");
      return 0;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      assert(0 && "Cannot get the size of a wstring");
      return 0;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      assert(0 && "Cannot get the size of a nested message");
      return 0;
    default:
      assert(0 && "Cannot get the size of an unknown message type");
      return 0;
  }
}


std::string
member_value_to_string(uint8_t type_id, const void * member_data)
{
  std::stringstream value;
  switch (type_id) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      value << *reinterpret_cast<const float*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      value << *reinterpret_cast<const double*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      value << *reinterpret_cast<const long double*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      value << *reinterpret_cast<const unsigned char*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      value << *reinterpret_cast<const char16_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      value << *reinterpret_cast<const bool*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      value << *reinterpret_cast<const unsigned char*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      value << *reinterpret_cast<const uint8_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      value << *reinterpret_cast<const int8_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      value << *reinterpret_cast<const uint16_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      value << *reinterpret_cast<const int16_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      value << *reinterpret_cast<const uint32_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      value << *reinterpret_cast<const int32_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      value << *reinterpret_cast<const uint64_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      value << *reinterpret_cast<const int64_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      value << reinterpret_cast<const rosidl_runtime_c__String *>(member_data)->data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      value << reinterpret_cast<const rosidl_runtime_c__U16String *>(member_data)->data;
      value << u16string_to_string(
        std::u16string(reinterpret_cast<const char16_t *>(
          reinterpret_cast<const rosidl_runtime_c__U16String *>(member_data)->data)));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      value << "[Nested message]";
      break;
    default:
      value << "Unknown value for unknown type";
      break;
  }
  return value.str();
}


void
add_indent(size_t indent_level, std::stringstream &output)
{
  for (size_t ii = 0; ii < indent_level; ++ii) {
    output << "  ";
  }
}


std::string
member_info_to_string(const MemberInfo &member_info)
{
  std::stringstream result;
  result << member_info.name_ << " (";
  if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
    // Nested message member
    const TypeInfo * nested_type_info = reinterpret_cast<const TypeInfo *>(
      member_info.members_->data);
    result << nested_type_info->message_namespace_ << '/' << nested_type_info->message_name_;
  } else {
    // POD member
    result << member_type_to_string(member_info);
  }
  if (member_info.is_array_) {
    result << '[';
    if (member_info.is_upper_bound_) {
      result << "<=";
    }
    if (member_info.array_size_ > 0) {
      result << member_info.array_size_;
    }
    result << ']';
  }
  result << ')';
  return result.str();
}


template<typename T>
void
dynamic_array_to_string_impl(T * array, std::stringstream &output)
{
  output << array->data[0];
  for (size_t ii = 1; ii < array->size; ++ii) {
    output << ", " << array->data[ii];
  }
}


void
dynamic_array_to_string(
  const MemberInfo &member_info,
  uint8_t * member_data,
  std::stringstream &output)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__float__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__double__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__long_double__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__char__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__wchar__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__boolean__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__octet__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__uint8__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__int8__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__uint16__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__int16__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__uint32__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__int32__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__uint64__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      dynamic_array_to_string_impl(
        reinterpret_cast<rosidl_runtime_c__int64__Sequence *>(member_data),
        output);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      assert(0 && "Cannot print an array of strings");
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      assert(0 && "Cannot print an array of wstrings");
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      assert(0 && "Cannot print an array of nested messages");
      break;
    default:
      assert(0 && "Cannot print an array of an unknown message type");
      break;
  }
}


void
fixed_array_to_string(
  const MemberInfo &member_info,
  uint8_t * member_data,
  std::stringstream &output)
{
  output << member_value_to_string(member_info.type_id_, &member_data[0]);
  for (size_t ii = 1; ii < member_info.array_size_; ++ii) {
    output << ", " << member_value_to_string(
      member_info.type_id_,
      &member_data[ii * size_of_member_type(member_info.type_id_)]);
  }
}


void
array_to_string(
  const MemberInfo &member_info,
  uint8_t * member_data,
  std::stringstream &output)
{
  output << '[';
  if (member_info.is_upper_bound_ || member_info.array_size_ == 0) {
    dynamic_array_to_string(member_info, member_data, output);
  } else {
    fixed_array_to_string(member_info, member_data, output);
  }
  output << ']';
}


void
member_to_string(
  const MemberInfo &member_info,
  uint8_t * member_data,
  size_t indent_level,
  std::stringstream &output)
{
  if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
    // Nested message member
    RosMessage nested_member{
      reinterpret_cast<const TypeInfo *>(member_info.members_->data),
      member_data};
    add_indent(indent_level, output);
    output << member_info_to_string(member_info) << "):" << std::endl;
    message_to_string(nested_member, indent_level + 1, output);
  } else {
    add_indent(indent_level, output);
    output << member_info_to_string(member_info) << ":\t";
    if (member_info.is_array_) {
      array_to_string(member_info, member_data, output);
      output << std::endl;
    } else {
      // POD member
      output << member_value_to_string(member_info.type_id_, member_data);
      output << std::endl;
    }
  }
}


void
message_to_string(
  RosMessage &message,
  size_t indent_level,
  std::stringstream &output)
{
  for (uint32_t ii = 0; ii < message.type_info->member_count_; ++ii) {
    uint8_t * member_data = &message.data[message.type_info->members_[ii].offset_];
    member_to_string(message.type_info->members_[ii], member_data, indent_level, output);
  }
}


int
main(int argc, char ** argv) {
  auto args = parse_arguments(argc, argv);

  std::string msg_namespace(argv[1]);
  std::string msg_type(argv[2]);

  rcl_init_options_t options = rcl_get_zero_initialized_init_options();
  rcl_ret_t ret = rcl_init_options_init(&options, rcl_get_default_allocator());
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init options failed");
    return 1;
  }

  rcl_context_t context = rcl_get_zero_initialized_context();
  ret = rcl_init(argc, argv, &options, &context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init failed");
    return 1;
  }
  ret = rcl_init_options_fini(&options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init_options fini failed");
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating node");
  rcl_node_options_t node_options = rcl_node_get_default_options();
  rcl_node_t node = rcl_get_zero_initialized_node();
  ret = rcl_node_init(&node, "dynmsg_test", "", &context, &node_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node init failed");
    return 1;
  }

  RosMessage message;
  if (ros_message_init(msg_namespace.c_str(), msg_type.c_str(), &message) != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "Message init failed");
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating subscription");
  rcl_subscription_t sub = rcl_get_zero_initialized_subscription();
  rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
  const auto* type_support = get_type_support(msg_namespace, msg_type);
  if (type_support == nullptr) {
    return 1;
  }
  ret = rcl_subscription_init(&sub, &node, type_support, "dynmsg", &sub_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "subscription init failed");
    return 1;
  }

  bool running = true;
  while (running) {
    size_t count{0};
    ret = rmw_subscription_count_matched_publishers(rcl_subscription_get_rmw_handle(&sub), &count);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "pub count failed");
      return 1;
    }
    RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "There are %ld matched publishers", count);
    if (count > 0) {
      break;
    }
    sleep(0.25);
  }

  bool taken = false;
  while (!taken) {
    taken = false;
    ret = rmw_take(rcl_subscription_get_rmw_handle(&sub), message.data, &taken, nullptr);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "take failed");
      return 1;
    }
    if (taken) {
      RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Received data");
      break;
    }
  }

  std::stringstream output;
  output << message.type_info->message_namespace_ << '/' <<
    message.type_info->message_name_ << std::endl;
  message_to_string(message, 1, output);
  std::cout << output.str();

  ret = rcl_node_fini(&node);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node fini failed");
    return 1;
  }
  ret = rcl_shutdown(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "shutdown failed");
    return 1;
  }
  ret = rcl_context_fini(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "context fini failed");
    return 1;
  }
  return 0;
}
