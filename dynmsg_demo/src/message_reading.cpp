#include "message_reading.hpp"

#include <dlfcn.h>

#include <clocale>
#include <iostream>
#include <locale>
#include <memory>
#include <sstream>
#include <vector>

#include "cli.hpp"
#include "string_utils.hpp"
#include "typesupport_utils.hpp"

#include "rcl/context.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/rcl.h"
#include "rcl/subscription.h"
#include "rcl/types.h"
#include "rcutils/logging_macros.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/u16string.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/field_types.h"


std::string
member_type_to_string(const MemberInfo &member_info)
{
  std::stringstream result;
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      result << "float";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      result << "double";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      result << "long double";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      result << "char";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      result << "wchar";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      result << "boolean";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      result << "octet";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      result << "uint8";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      result << "int8";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      result << "uint16";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      result << "int16";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      result << "uint32";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      result << "int32";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      result << "uint64";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      result << "int64";
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      result << "string";
      if (member_info.string_upper_bound_ > 0) {
        result << "<=" << member_info.string_upper_bound_;
      }
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      result << "wstring";
      if (member_info.string_upper_bound_ > 0) {
        result << "<=" << member_info.string_upper_bound_;
      }
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      result <<
        reinterpret_cast<const TypeInfo *>(member_info.members_->data)->message_namespace_ <<
        "/" <<
        reinterpret_cast<const TypeInfo *>(member_info.members_->data)->message_name_;
      break;
    default:
      result << "UNKNOWN";
      break;
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
  return result.str();
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
      return sizeof(rosidl_runtime_c__String);
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      return sizeof(rosidl_runtime_c__U16String);
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      assert(0 && "Cannot get the size of a nested message");
      return 0;
    default:
      assert(0 && "Cannot get the size of an unknown message type");
      return 0;
  }
}


void member_to_yaml_array_item(
  const MemberInfo &member_info,
  const uint8_t * member_data,
  YAML::Node &array_node)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      array_node.push_back(*reinterpret_cast<const float*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      array_node.push_back(*reinterpret_cast<const double*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      array_node.push_back(*reinterpret_cast<const long double*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      array_node.push_back(*reinterpret_cast<const uint8_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      array_node.push_back(*reinterpret_cast<const uint16_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      array_node.push_back(*reinterpret_cast<const bool*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      array_node.push_back(*reinterpret_cast<const uint8_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      array_node.push_back(*reinterpret_cast<const uint8_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      array_node.push_back(*reinterpret_cast<const int8_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      array_node.push_back(*reinterpret_cast<const uint16_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      array_node.push_back(*reinterpret_cast<const int16_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      array_node.push_back(*reinterpret_cast<const uint32_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      array_node.push_back(*reinterpret_cast<const int32_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      array_node.push_back(*reinterpret_cast<const uint64_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      array_node.push_back(*reinterpret_cast<const int64_t*>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      array_node.push_back(
        std::string(reinterpret_cast<const rosidl_runtime_c__String *>(member_data)->data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      array_node.push_back(u16string_to_string(
        std::u16string(reinterpret_cast<const char16_t *>(
          reinterpret_cast<const rosidl_runtime_c__U16String *>(member_data)->data))));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      nested_member.data = const_cast<uint8_t*>(member_data);
      array_node.push_back(message_to_yaml(nested_member));
      break;
    default:
      array_node.push_back("Unknown value for unknown type");
      break;
  }
}


void member_to_yaml(
  const MemberInfo &member_info,
  const uint8_t * member_data,
  YAML::Node &member)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      member["value"] = *reinterpret_cast<const float*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      member["value"] = *reinterpret_cast<const double*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      member["value"] = *reinterpret_cast<const long double*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      member["value"] = *reinterpret_cast<const uint8_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      member["value"] = *reinterpret_cast<const uint16_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      member["value"] = *reinterpret_cast<const bool*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      member["value"] = *reinterpret_cast<const uint8_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      member["value"] = *reinterpret_cast<const uint8_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      member["value"] = *reinterpret_cast<const int8_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      member["value"] = *reinterpret_cast<const uint16_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      member["value"] = *reinterpret_cast<const int16_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      member["value"] = *reinterpret_cast<const uint32_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      member["value"] = *reinterpret_cast<const int32_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      member["value"] = *reinterpret_cast<const uint64_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      member["value"] = *reinterpret_cast<const int64_t*>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      member["value"] = reinterpret_cast<const rosidl_runtime_c__String *>(member_data)->data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      member["value"] = u16string_to_string(
        std::u16string(reinterpret_cast<const char16_t *>(
          reinterpret_cast<const rosidl_runtime_c__U16String *>(member_data)->data)));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      nested_member.data = const_cast<uint8_t*>(member_data);
      member["value"] = message_to_yaml(nested_member);
      break;
    default:
      member["value"] = "Unknown value for unknown type";
      break;
  }
}


template<typename T>
void
dynamic_array_to_string_impl(const MemberInfo &member_info, T * array, YAML::Node &array_node)
{
  for (size_t ii = 0; ii < array->size; ++ii) {
    member_to_yaml_array_item(
      member_info,
      reinterpret_cast<const uint8_t *>(&array->data[ii]),
      array_node);
  }
}


void
dynamic_array_to_yaml(
  const MemberInfo &member_info,
  const uint8_t * member_data,
  YAML::Node &array_node)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__float__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__double__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__long_double__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__char__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__wchar__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__boolean__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__octet__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint8__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int8__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint16__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int16__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint32__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int32__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint64__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int64__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__String__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      dynamic_array_to_string_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__U16String__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      // We do not know the specific type of the sequence, but they all follow the same structure
      // pattern, where a pointer to the data is first, followed by the element count, followed by
      // the capacity
      size_t element_count;
      element_count = static_cast<size_t>(member_data[sizeof(void*)]);
      size_t element_size;
      element_size = sizeof(void*) + sizeof(size_t) + sizeof(size_t);
      for (size_t ii = 0; ii < element_count; ++ii) {
        RosMessage nested_member;
        nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
        nested_member.data = const_cast<uint8_t*>(&member_data[ii * element_size]);
        array_node.push_back(message_to_yaml(nested_member));
      }
      break;
    default:
      array_node.push_back("Unknown value for unknown type");
      break;
  }
}


void fixed_array_to_yaml(
  const MemberInfo &member_info,
  uint8_t * member_data,
  YAML::Node &array_node)
{
  size_t element_size(0);
  if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
    element_size = reinterpret_cast<const TypeInfo *>(member_info.members_->data)->size_of_;
  } else {
    element_size = size_of_member_type(member_info.type_id_);
  }
  for (size_t ii = 0; ii < member_info.array_size_; ++ii) {
    member_to_yaml_array_item(member_info, &member_data[ii * element_size], array_node);
  }
}


YAML::Node member_to_yaml(
  const MemberInfo &member_info,
  uint8_t * member_data)
{
  YAML::Node member;
  member["type"] = member_type_to_string(member_info);
  if (member_info.default_value_ != nullptr) {
    member["default"] = "default value here";
  }

  if (member_info.is_array_) {
    YAML::Node array;
    if (member_info.is_upper_bound_ || member_info.array_size_ == 0) {
      dynamic_array_to_yaml(member_info, member_data, array);
    } else {
      fixed_array_to_yaml(member_info, member_data, array);
    }
    member["value"] = array;
  } else {
    if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      nested_member.data = const_cast<uint8_t*>(member_data);
      member["value"] = message_to_yaml(nested_member);
    } else {
      member_to_yaml(member_info, member_data, member);
    }
  }

  return member;
}


YAML::Node
message_to_yaml(const RosMessage &message)
{
  YAML::Node yaml_msg;
  for (uint32_t ii = 0; ii < message.type_info->member_count_; ++ii) {
    const MemberInfo &member_info = message.type_info->members_[ii];
    uint8_t * member_data = &message.data[member_info.offset_];
    yaml_msg[member_info.name_] = member_to_yaml(member_info, member_data);
  }
  return yaml_msg;
}
