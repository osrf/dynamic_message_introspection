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

#include "dynmsg_demo/msg_parser.hpp"
#include "dynmsg_demo/string_utils.hpp"

#include <yaml-cpp/yaml.h>

#include <rosidl_runtime_c/string.h>
#include <rosidl_runtime_c/string_functions.h>
#include <rosidl_runtime_c/u16string.h>
#include <rosidl_runtime_c/u16string_functions.h>
#include <rosidl_runtime_c/primitives_sequence_functions.h>
#include <rosidl_typesupport_introspection_c/field_types.h>
#include <rcutils/logging_macros.h>

// forward declare
void yaml_to_rosmsg_impl(
  const YAML::Node& root,
  const TypeInfo* typeinfo,
  uint8_t* buffer
);

template<typename SequenceType>
using SequenceInitFunc = bool (*)(SequenceType*, size_t);

template<int RosTypeId>
struct TypeMapping {};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT> {
  using CppType = float;
  using SequenceType = rosidl_runtime_c__float32__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__float32__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE> {
  using CppType = double;
  using SequenceType = rosidl_runtime_c__double__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__double__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE> {
  using CppType = long double;
  using SequenceType = rosidl_runtime_c__long_double__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__long_double__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR> {
  using CppType = signed char;
  using SequenceType = rosidl_runtime_c__char__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__char__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR> {
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__wchar__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__wchar__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN> {
  using CppType = bool;
  using SequenceType = rosidl_runtime_c__bool__Sequence;
    static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__bool__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET> {
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__octet__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__octet__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8> {
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__uint8__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__uint8__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT8> {
  using CppType = int8_t;
  using SequenceType = rosidl_runtime_c__int8__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__int8__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT16> {
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__uint16__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__uint16__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT16> {
  using CppType = int16_t;
  using SequenceType = rosidl_runtime_c__int16__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__int16__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT32> {
  using CppType = uint32_t;
  using SequenceType = rosidl_runtime_c__uint32__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__uint32__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT32> {
  using CppType = int32_t;
  using SequenceType = rosidl_runtime_c__int32__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__int32__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT64> {
  using CppType = uint64_t;
  using SequenceType = rosidl_runtime_c__uint64__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__uint64__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT64> {
  using CppType = int64_t;
  using SequenceType = rosidl_runtime_c__int64__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__int64__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING> {
  using CppType = rosidl_runtime_c__String;
  using SequenceType = rosidl_runtime_c__String__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__String__Sequence__init;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING> {
  using CppType = rosidl_runtime_c__U16String;
  using SequenceType = rosidl_runtime_c__U16String__Sequence;
  static constexpr SequenceInitFunc<SequenceType> sequence_init
    = rosidl_runtime_c__U16String__Sequence__init;
};

template<int RosTypeId>
void write_member_item(
  const YAML::Node& yaml,
  uint8_t* buffer
) {
  using CppType = typename TypeMapping<RosTypeId>::CppType;
  *reinterpret_cast<CppType*>(buffer) = yaml.as<CppType>();
}

template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>(
  const YAML::Node& yaml,
  uint8_t* buffer
) {
  using CppType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>::CppType;
  std::string s = yaml.as<std::string>();
  CppType* ros_string = reinterpret_cast<CppType*>(buffer);
  if (!rosidl_runtime_c__String__assign(ros_string, s.data())) {
    throw std::runtime_error("error assigning rosidl string");
  }
}

template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>(
  const YAML::Node& yaml,
  uint8_t* buffer
) {
  using CppType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>::CppType;
  std::u16string u16s = string_to_u16string(yaml.as<std::string>());
  CppType* ros_string = reinterpret_cast<CppType*>(buffer);
  if (
    !rosidl_runtime_c__U16String__assign(
      ros_string, reinterpret_cast<uint16_t*>(const_cast<char16_t*>(u16s.data())))
  ) {
    throw std::runtime_error("error assigning rosidl string");
  }
}

template<int RosTypeId>
void write_member_sequence(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  using SequenceType = typename TypeMapping<RosTypeId>::SequenceType;

  if (member.is_upper_bound_ && yaml.size() > member.array_size_) {
    throw std::runtime_error("yaml sequence is more than capacity");
  }
  auto seq = reinterpret_cast<SequenceType*>(buffer);
  TypeMapping<RosTypeId>::sequence_init(seq, yaml.size());
  for (size_t i = 0; i < yaml.size(); i++) {
    write_member_item<RosTypeId>(
      yaml[i],
      reinterpret_cast<uint8_t*>(seq->data + i)
    );
  }
}

bool is_sequence(const MemberInfo& member) {
  // there isn't a "is_sequence" flag in the introspection data, from manual inspection, it looks
  // like,
  //
  // array:
  //   is_array == true
  //   array_size > 0
  //   is_upper_bound == false
  // bounded_sequences:
  //   is_array == true
  //   array_size > 0
  //   is_upper_bound == true
  // unbounded_sequence:
  //   is_array == true
  //   array_size == 0
  //   is_upper_bound == false
  //
  // Qn: What if there is an array with size of 0?
  if ((member.is_array_ && member.array_size_ == 0) || member.is_upper_bound_) {
    return true;
  }
  return false;
}

template<int RosTypeId>
void write_member(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  using CppType = typename TypeMapping<RosTypeId>::CppType;
  // arrays and sequences have different struct representation. An array is represented by a
  // classic c array (pointer with byte size == sizeof(type) * array_size).
  //
  // sequences on the other hand is a custom-defined struct with data, size and capacity members.
  if (is_sequence(member)) {
    write_member_sequence<RosTypeId>(yaml[member.name_], buffer + member.offset_, member);
    return;
  }

  if (member.is_array_) {
    for (size_t i = 0; i < member.array_size_; i++) {
      write_member_item<RosTypeId>(
        yaml[member.name_][i],
        buffer + member.offset_ + sizeof(CppType) * i
      );
    }
  } else {
    write_member_item<RosTypeId>(yaml[member.name_], buffer + member.offset_);
  }
}

void write_member_sequence_nested(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  if (member.is_upper_bound_ && yaml.size() > member.array_size_) {
    throw std::runtime_error("yaml sequence is more than capacity");
  }
  const TypeInfo* member_typeinfo = reinterpret_cast<const TypeInfo*>(member.members_->data);
  auto& seq = buffer;
  member.resize_function(seq, yaml.size());
  for (size_t i = 0; i < yaml.size(); i++) {
    yaml_to_rosmsg_impl(
      yaml[i],
      member_typeinfo,
      reinterpret_cast<uint8_t*>(member.get_function(seq, i))
    );
  }
}

void write_member_nested(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  if (is_sequence(member)) {
    write_member_sequence_nested(yaml[member.name_], buffer + member.offset_, member);
    return;
  }

  const TypeInfo* member_typeinfo = reinterpret_cast<const TypeInfo*>(member.members_->data);
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

void yaml_to_rosmsg_impl(
  const YAML::Node& root,
  const TypeInfo* typeinfo,
  uint8_t* buffer
) {
  for (uint32_t i = 0; i < typeinfo->member_count_; i++) {
    const auto& member = typeinfo->members_[i];

    if (!root[member.name_]) {
      continue;
    }

    switch (member.type_id_) {
      case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT8: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT8>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT16>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT16: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT16>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT32>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT32: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT32>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_UINT64>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT64: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_INT64>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_STRING: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING: {
        write_member<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE: {
        write_member_nested(root, buffer, member);
        break;
      }
      default: {
        throw std::runtime_error("unknown type");
      }
    }
  }
}

RosMessage yaml_to_rosmsg(
  const InterfaceTypeName &interface_type,
  const std::string& yaml_str
) {
  YAML::Node root = YAML::Load(yaml_str);
  RosMessage ros_msg;
  ros_message_init(interface_type, &ros_msg);
  yaml_to_rosmsg_impl(root, ros_msg.type_info, ros_msg.data);
  return ros_msg;
}
