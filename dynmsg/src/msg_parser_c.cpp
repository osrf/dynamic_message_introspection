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

#include <yaml-cpp/yaml.h>

#include <string>

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/u16string.h"
#include "rosidl_runtime_c/u16string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rcutils/logging_macros.h"
#include "rcutils/allocator.h"

#include "dynmsg/config.hpp"
#include "dynmsg/msg_parser.hpp"
#include "dynmsg/string_utils.hpp"

namespace dynmsg
{
namespace c
{

namespace impl
{

void yaml_to_rosmsg_impl(
  const YAML::Node & root,
  const TypeInfo * typeinfo,
  uint8_t * buffer);

// Helper structures to make the code cleaner
template<typename SequenceType>
using SequenceInitFunc = bool (*)(SequenceType *, size_t);

template<int RosTypeId>
struct TypeMapping {};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT>
{
  using CppType = float;
  using SequenceType = rosidl_runtime_c__float32__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__float32__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE>
{
  using CppType = double;
  using SequenceType = rosidl_runtime_c__double__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__double__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE>
{
  using CppType = long double;
  using SequenceType = rosidl_runtime_c__long_double__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__long_double__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR>
{
  using CppType = signed char;
  using SequenceType = rosidl_runtime_c__char__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__char__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR>
{
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__wchar__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__wchar__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN>
{
  using CppType = bool;
  using SequenceType = rosidl_runtime_c__bool__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__bool__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET>
{
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__octet__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__octet__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8>
{
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__uint8__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__uint8__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT8>
{
  using CppType = int8_t;
  using SequenceType = rosidl_runtime_c__int8__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__int8__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT16>
{
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__uint16__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__uint16__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT16>
{
  using CppType = int16_t;
  using SequenceType = rosidl_runtime_c__int16__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__int16__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT32>
{
  using CppType = uint32_t;
  using SequenceType = rosidl_runtime_c__uint32__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__uint32__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT32>
{
  using CppType = int32_t;
  using SequenceType = rosidl_runtime_c__int32__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__int32__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT64>
{
  using CppType = uint64_t;
  using SequenceType = rosidl_runtime_c__uint64__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__uint64__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT64>
{
  using CppType = int64_t;
  using SequenceType = rosidl_runtime_c__int64__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__int64__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>
{
  using CppType = rosidl_runtime_c__String;
  using SequenceType = rosidl_runtime_c__String__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__String__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>
{
  using CppType = rosidl_runtime_c__U16String;
  using SequenceType = rosidl_runtime_c__U16String__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init =
    rosidl_runtime_c__U16String__Sequence__init;
};

// Write an individual member into the binary message - generic
template<int RosTypeId>
void write_member_item(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType = typename TypeMapping<RosTypeId>::CppType;
  *reinterpret_cast<CppType *>(buffer) = yaml.as<CppType>();
}

#ifdef DYNMSG_YAML_CPP_BAD_INT8_HANDLING
// Write an individual member into the binary message - [u]int8_t (char, octet, uint8, int8)
// See config.hpp
template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR>(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR>::CppType;
  std::string s = yaml.as<std::string>();
  *reinterpret_cast<CppType *>(buffer) = (uint8_t)std::stoul(s);
}
template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET>(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType =
    typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET>::CppType;
  std::string s = yaml.as<std::string>();
  *reinterpret_cast<CppType *>(buffer) = (uint8_t)std::stoul(s);
}
template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8>(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType =
    typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8>::CppType;
  std::string s = yaml.as<std::string>();
  *reinterpret_cast<CppType *>(buffer) = (uint8_t)std::stoul(s);
}
template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_INT8>(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT8>::CppType;
  std::string s = yaml.as<std::string>();
  *reinterpret_cast<CppType *>(buffer) = (int8_t)std::stoi(s);
}
#endif  // DYNMSG_YAML_CPP_BAD_INT8_HANDLING

// Write an individual member into the binary message - string
template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType =
    typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>::CppType;
  std::string s = yaml.as<std::string>();
  CppType * ros_string = reinterpret_cast<CppType *>(buffer);
  if (!rosidl_runtime_c__String__assign(ros_string, s.data())) {
    throw std::runtime_error("error assigning rosidl string");
  }
}

// Write an individual member into the binary message - wstring
template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>(
  const YAML::Node & yaml,
  uint8_t * buffer)
{
  using CppType =
    typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>::CppType;
  std::u16string u16s = string_to_u16string(yaml.as<std::string>());
  CppType * ros_string = reinterpret_cast<CppType *>(buffer);
  if (
    !rosidl_runtime_c__U16String__assign(
      ros_string, reinterpret_cast<uint16_t *>(const_cast<char16_t *>(u16s.data()))))
  {
    throw std::runtime_error("error assigning rosidl string");
  }
}

// Write a sequence member into the binary message - generic
template<int RosTypeId>
void write_member_sequence(const YAML::Node & yaml, uint8_t * buffer, const MemberInfo & member)
{
  using SequenceType = typename TypeMapping<RosTypeId>::SequenceType;

  if (member.is_upper_bound_ && yaml.size() > member.array_size_) {
    throw std::runtime_error("yaml sequence is more than capacity");
  }
  auto seq = reinterpret_cast<SequenceType *>(buffer);
  TypeMapping<RosTypeId>::sequence_init(seq, yaml.size());
  for (size_t i = 0; i < yaml.size(); i++) {
    write_member_item<RosTypeId>(
      yaml[i],
      reinterpret_cast<uint8_t *>(seq->data + i)
    );
  }
}

// Check if a field is a sequence of some kind
bool is_sequence(const MemberInfo & member)
{
  // There isn't a "is_sequence" flag in the introspection data. It has to be inferred from several
  // flags:
  //
  // fixed-length array:
  //   is_array == true
  //   array_size > 0
  //   is_upper_bound == false
  // bounded_sequence (has a maximum size but may be smaller):
  //   is_array == true
  //   array_size > 0
  //   is_upper_bound == true
  // unbounded_sequence (no maximum size):
  //   is_array == true
  //   array_size == 0
  //   is_upper_bound == false
  //
  // Unhandled is the case of an array with size 0
  if ((member.is_array_ && member.array_size_ == 0) || member.is_upper_bound_) {
    return true;
  }
  return false;
}

// Convert a YAML node into a field in the binary ROS message - generic
template<int RosTypeId>
void write_member(const YAML::Node & yaml, uint8_t * buffer, const MemberInfo & member)
{
  using CppType = typename TypeMapping<RosTypeId>::CppType;
  // Arrays and sequences have different struct representation. An array is represented by a
  // classic C array (pointer with data size == sizeof(type) * array_size).
  //
  // Sequences on the other hand use a custom-defined struct with data, size and capacity members.

  // Handle sequences
  if (is_sequence(member)) {
    write_member_sequence<RosTypeId>(yaml[member.name_], buffer + member.offset_, member);
    return;
  }

  // Handle classic C arrays
  if (member.is_array_) {
    for (size_t i = 0; i < member.array_size_; i++) {
      write_member_item<RosTypeId>(
        yaml[member.name_][i],
        buffer + member.offset_ + sizeof(CppType) * i
      );
    }
  } else {
    // Handle single-item members
    write_member_item<RosTypeId>(yaml[member.name_], buffer + member.offset_);
  }
}

// Convert a nested YAML sequence node
void write_member_sequence_nested(
  const YAML::Node & yaml,
  uint8_t * buffer,
  const MemberInfo & member)
{
  if (member.is_upper_bound_ && yaml.size() > member.array_size_) {
    throw std::runtime_error("yaml sequence is more than capacity");
  }
  const TypeInfo * member_typeinfo = reinterpret_cast<const TypeInfo *>(member.members_->data);
  auto & seq = buffer;
  member.resize_function(seq, yaml.size());
  for (size_t i = 0; i < yaml.size(); i++) {
    yaml_to_rosmsg_impl(
      yaml[i],
      member_typeinfo,
      reinterpret_cast<uint8_t *>(member.get_function(seq, i))
    );
  }
}

// Convert a nested YAML node
void write_member_nested(const YAML::Node & yaml, uint8_t * buffer, const MemberInfo & member)
{
  if (is_sequence(member)) {
    write_member_sequence_nested(yaml[member.name_], buffer + member.offset_, member);
    return;
  }

  const TypeInfo * member_typeinfo = reinterpret_cast<const TypeInfo *>(member.members_->data);
  if (member.is_array_) {
    for (size_t i = 0; i < yaml[member.name_].size(); i++) {
      yaml_to_rosmsg_impl(
        yaml[member.name_][i],
        member_typeinfo, buffer + member.offset_ + member_typeinfo->size_of_ * i
      );
    }
  } else {
    yaml_to_rosmsg_impl(yaml[member.name_], member_typeinfo, buffer + member.offset_);
  }
}


// Convert a YAML representation to a binary ROS message by looping over the expected fields of the
// ROS message and getting their values from the YAML
void yaml_to_rosmsg_impl(
  const YAML::Node & root,
  const TypeInfo * typeinfo,
  uint8_t * buffer)
{
  for (uint32_t i = 0; i < typeinfo->member_count_; i++) {
    const auto & member = typeinfo->members_[i];

    if (!root[member.name_]) {
      continue;
    }

    switch (member.type_id_) {
      case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE>(
          root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT8>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT16>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT16>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT32>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT32>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT64>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT64>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>(root, buffer, member);
        break;
      case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
        write_member_nested(root, buffer, member);
        break;
      default:
        throw std::runtime_error("unknown type");
    }
  }
}

}  // namespace impl

RosMessage yaml_and_typeinfo_to_rosmsg(
  const TypeInfo * type_info,
  const std::string & yaml_str,
  rcutils_allocator_t * allocator)
{
  rcutils_allocator_t default_allocator = rcutils_get_default_allocator();
  if (!allocator) {
    allocator = &default_allocator;
  }
  // Parse the YAML representation to an in-memory representation
  YAML::Node root = YAML::Load(yaml_str);
  RosMessage ros_msg;
  // Load the introspection information and allocate space for the ROS message's binary
  // representation
  if (DYNMSG_RET_OK != dynmsg::c::ros_message_with_typeinfo_init(type_info, &ros_msg, allocator)) {
    return {nullptr, nullptr};
  }
  // Convert the YAML representation to a binary representation
  impl::yaml_to_rosmsg_impl(root, ros_msg.type_info, ros_msg.data);
  return ros_msg;
}

RosMessage yaml_to_rosmsg(
  const InterfaceTypeName & interface_type,
  const std::string & yaml_str)
{
  const auto * type_info = dynmsg::c::get_type_info(interface_type);
  if (nullptr == type_info) {
    return {nullptr, nullptr};
  }
  return dynmsg::c::yaml_and_typeinfo_to_rosmsg(type_info, yaml_str, nullptr);
}

}  // namespace c
}  // namespace dynmsg
