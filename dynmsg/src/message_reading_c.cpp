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

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "rcutils/logging_macros.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/u16string.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/field_types.h"

#include "dynmsg/config.hpp"
#include "dynmsg/message_reading.hpp"
#include "dynmsg/string_utils.hpp"
#include "dynmsg/typesupport.hpp"

namespace dynmsg
{
namespace c
{

namespace impl
{

#ifndef DYNMSG_VALUE_ONLY
// Convert primitive ROS types to a string representation
std::string
member_type_to_string(const MemberInfo & member_info)
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
      // Strings may have an upper bound
      if (member_info.string_upper_bound_ > 0) {
        result << "<=" << member_info.string_upper_bound_;
      }
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      result << "wstring";
      // WStrings may have an upper bound
      if (member_info.string_upper_bound_ > 0) {
        result << "<=" << member_info.string_upper_bound_;
      }
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      // For nested types, the string representation must include the name space as well as the
      // type name
      result <<
        reinterpret_cast<const TypeInfo *>(member_info.members_->data)->message_namespace_ <<
        "/" <<
        reinterpret_cast<const TypeInfo *>(member_info.members_->data)->message_name_;
      break;
    default:
      // Don't throw an error, just print out "UNKNOWN" then keep persevering through the message
      result << "UNKNOWN";
      break;
  }
  // If this member is a sequence of some kind, indicate that in the type
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
#endif  // DYNMSG_VALUE_ONLY


// Get the size of primitive types
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


// Convert the binary data for an individual element of an array member to YAML
void member_to_yaml_array_item(
  const MemberInfo & member_info,
  const uint8_t * member_data,
  YAML::Node & array_node)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      array_node.push_back(*reinterpret_cast<const float *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      array_node.push_back(*reinterpret_cast<const double *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      array_node.push_back(*reinterpret_cast<const long double *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      array_node.push_back(std::to_string(*reinterpret_cast<const uint8_t *>(member_data)));
#else
      array_node.push_back(*reinterpret_cast<const uint8_t *>(member_data));
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      array_node.push_back(*reinterpret_cast<const uint16_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      array_node.push_back(*reinterpret_cast<const bool *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      array_node.push_back(std::to_string(*reinterpret_cast<const uint8_t *>(member_data)));
#else
      array_node.push_back(*reinterpret_cast<const uint8_t *>(member_data));
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      array_node.push_back(std::to_string(*reinterpret_cast<const uint8_t *>(member_data)));
#else
      array_node.push_back(*reinterpret_cast<const uint8_t *>(member_data));
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      array_node.push_back(std::to_string(*reinterpret_cast<const int8_t *>(member_data)));
#else
      array_node.push_back(*reinterpret_cast<const int8_t *>(member_data));
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      array_node.push_back(*reinterpret_cast<const uint16_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      array_node.push_back(*reinterpret_cast<const int16_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      array_node.push_back(*reinterpret_cast<const uint32_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      array_node.push_back(*reinterpret_cast<const int32_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      array_node.push_back(*reinterpret_cast<const uint64_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      array_node.push_back(*reinterpret_cast<const int64_t *>(member_data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      array_node.push_back(
        std::string(reinterpret_cast<const rosidl_runtime_c__String *>(member_data)->data));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      // WStrings require going through some intermediate formats
      array_node.push_back(
        u16string_to_string(
          std::u16string(
            reinterpret_cast<const char16_t *>(
              reinterpret_cast<const rosidl_runtime_c__U16String *>(member_data)->data))));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      // For nested types, don't copy the data out of the buffer directly. Recursively read the
      // nested type into the YAML.
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      nested_member.data = const_cast<uint8_t *>(member_data);
      array_node.push_back(dynmsg::c::message_to_yaml(nested_member));
      break;
    default:
      array_node.push_back("Unknown value for unknown type");
      break;
  }
}

// Convert an individual member's value from binary to YAML
void basic_value_to_yaml(
  const MemberInfo & member_info,
  const uint8_t * member_data,
  YAML::Node & member)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      member["value"] = *reinterpret_cast<const float *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      member["value"] = *reinterpret_cast<const double *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      member["value"] = *reinterpret_cast<const long double *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      member["value"] = std::to_string(*reinterpret_cast<const uint8_t *>(member_data));
#else
      member["value"] = *reinterpret_cast<const uint8_t *>(member_data);
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      member["value"] = *reinterpret_cast<const uint16_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      member["value"] = *reinterpret_cast<const bool *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      member["value"] = std::to_string(*reinterpret_cast<const uint8_t *>(member_data));
#else
      member["value"] = *reinterpret_cast<const uint8_t *>(member_data);
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      member["value"] = std::to_string(*reinterpret_cast<const uint8_t *>(member_data));
#else
      member["value"] = *reinterpret_cast<const uint8_t *>(member_data);
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
      member["value"] = std::to_string(*reinterpret_cast<const int8_t *>(member_data));
#else
      member["value"] = *reinterpret_cast<const int8_t *>(member_data);
#endif
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      member["value"] = *reinterpret_cast<const uint16_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      member["value"] = *reinterpret_cast<const int16_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      member["value"] = *reinterpret_cast<const uint32_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      member["value"] = *reinterpret_cast<const int32_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      member["value"] = *reinterpret_cast<const uint64_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      member["value"] = *reinterpret_cast<const int64_t *>(member_data);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      member["value"] = reinterpret_cast<const rosidl_runtime_c__String *>(member_data)->data;
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      // WStrings require going through some intermediate formats
      member["value"] = u16string_to_string(
        std::u16string(
          reinterpret_cast<const char16_t *>(
            reinterpret_cast<const rosidl_runtime_c__U16String *>(member_data)->data)));
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      // For nested types, don't copy the data out of the buffer directly. Recursively read the
      // nested type into the YAML.
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      nested_member.data = const_cast<uint8_t *>(member_data);
      member["value"] = dynmsg::c::message_to_yaml(nested_member);
      break;
    default:
      member["value"] = "Unknown value for unknown type";
      break;
  }
}

// Convert a dynamically-sized sequence to YAML - implementation function
template<typename T>
void
dynamic_array_to_yaml_impl(const MemberInfo & member_info, T * array, YAML::Node & array_node)
{
  for (size_t ii = 0; ii < array->size; ++ii) {
    member_to_yaml_array_item(
      member_info,
      reinterpret_cast<const uint8_t *>(&array->data[ii]),
      array_node);
  }
}

// Convert a dynamically-sized sequence to YAML
void
dynamic_array_to_yaml(
  const MemberInfo & member_info,
  const uint8_t * member_data,
  YAML::Node & array_node)
{
  switch (member_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__float__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__double__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__long_double__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__char__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__wchar__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__boolean__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__octet__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint8__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int8__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint16__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int16__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint32__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int32__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__uint64__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__int64__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__String__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      dynamic_array_to_yaml_impl(
        member_info,
        reinterpret_cast<const rosidl_runtime_c__U16String__Sequence *>(member_data),
        array_node);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      // We do not know the specific type of the sequence because the type is not available at
      // compile-time, but they all follow the same structure pattern, where a pointer to the data
      // is first, followed by the element count, followed by the capacity
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      uint8_t * element_data;
      memcpy(&element_data, member_data, sizeof(void *));
      size_t element_size;
      element_size = nested_member.type_info->size_of_;
      size_t element_count;
      element_count = static_cast<size_t>(member_data[sizeof(void *)]);
      for (size_t ii = 0; ii < element_count; ++ii) {
        nested_member.data = element_data + ii * element_size;
        // Recursively read the nested type into the array element in the YAML representation
        array_node.push_back(dynmsg::c::message_to_yaml(nested_member));
      }
      break;
    default:
      // Store an error string and keep going
      array_node.push_back("Unknown value for unknown type");
      break;
  }
}

// Convert a fixed-sized sequence (a C-style array) to YAML
void fixed_array_to_yaml(
  const MemberInfo & member_info,
  uint8_t * member_data,
  YAML::Node & array_node)
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

// Read one member of a message into a YAML node and return that node
YAML::Node member_to_yaml(
  const MemberInfo & member_info,
  uint8_t * member_data)
{
  YAML::Node member;
#ifndef DYNMSG_VALUE_ONLY
  member["type"] = member_type_to_string(member_info);
  if (member_info.default_value_ != nullptr) {
    member["default"] = "default value here";
  }
#endif

  if (member_info.is_array_) {
    YAML::Node array;
    if (member_info.is_upper_bound_ || member_info.array_size_ == 0) {
      dynamic_array_to_yaml(member_info, member_data, array);
    } else {
      fixed_array_to_yaml(member_info, member_data, array);
    }
#ifdef DYNMSG_VALUE_ONLY
    return array;
#else
    member["value"] = array;
#endif
  } else {
    if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
      RosMessage nested_member;
      nested_member.type_info = reinterpret_cast<const TypeInfo *>(member_info.members_->data);
      nested_member.data = const_cast<uint8_t *>(member_data);
#ifdef DYNMSG_VALUE_ONLY
      return dynmsg::c::message_to_yaml(nested_member);
#else
      member["value"] = ::message_to_yaml(nested_member);
#endif
    } else {
      basic_value_to_yaml(member_info, member_data, member);
#ifdef DYNMSG_VALUE_ONLY
      return member["value"];
#endif
    }
  }

  return member;
}

}  // namespace impl

YAML::Node
message_to_yaml(const RosMessage & message)
{
  YAML::Node yaml_msg;
  // Iterate over the members of the message, converting the binary data for each into a node in
  // the YAML representation
  for (uint32_t ii = 0; ii < message.type_info->member_count_; ++ii) {
    // Get the introspection information for this particular member
    const MemberInfo & member_info = message.type_info->members_[ii];
    // Get a pointer to the member's data in the binary buffer
    uint8_t * member_data = &message.data[member_info.offset_];
    // Recursively (because some members may be non-primitive types themeslves) convert the member
    // to YAML
    yaml_msg[member_info.name_] = dynmsg::c::impl::member_to_yaml(member_info, member_data);
  }
  return yaml_msg;
}

}  // namespace c
}  // namespace dynmsg
