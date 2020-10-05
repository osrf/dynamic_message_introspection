#include "dynmsg_demo/msg_parser.hpp"
#include "dynmsg_demo/string_utils.hpp"

#include <yaml-cpp/yaml.h>

#include <rosidl_runtime_c/string.h>
#include <rosidl_runtime_c/u16string.h>
#include <rosidl_typesupport_introspection_c/field_types.h>
#include <rcutils/logging_macros.h>

// forward declare
void yaml_to_rosmsg_impl(
  const YAML::Node& root,
  const TypeInfo* typeinfo,
  uint8_t* buffer
);

template<int RosTypeId>
struct TypeMapping {};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT> {
  using CppType = float;
  using SequenceType = rosidl_runtime_c__float32__Sequence;
  using RosType = float;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE> {
  using CppType = double;
  using SequenceType = rosidl_runtime_c__double__Sequence;
  using RosType = double;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE> {
  using CppType = long double;
  using SequenceType = rosidl_runtime_c__long_double__Sequence;
  using RosType = long double;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR> {
  using CppType = signed char;
  using SequenceType = rosidl_runtime_c__char__Sequence;
  using RosType = signed char;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR> {
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__wchar__Sequence;
  using RosType = uint16_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN> {
  using CppType = bool;
  using SequenceType = rosidl_runtime_c__bool__Sequence;
  using RosType = bool;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET> {
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__octet__Sequence;
  using RosType = uint8_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8> {
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__uint8__Sequence;
  using RosType = uint8_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT8> {
  using CppType = int8_t;
  using SequenceType = rosidl_runtime_c__int8__Sequence;
  using RosType = int8_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT16> {
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__uint16__Sequence;
  using RosType = uint16_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT16> {
  using CppType = int16_t;
  using SequenceType = rosidl_runtime_c__int16__Sequence;
  using RosType = int16_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT32> {
  using CppType = uint32_t;
  using SequenceType = rosidl_runtime_c__uint32__Sequence;
  using RosType = uint32_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT32> {
  using CppType = int32_t;
  using SequenceType = rosidl_runtime_c__int32__Sequence;
  using RosType = int32_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT64> {
  using CppType = uint64_t;
  using SequenceType = rosidl_runtime_c__uint64__Sequence;
  using RosType = uint64_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT64> {
  using CppType = int64_t;
  using SequenceType = rosidl_runtime_c__int64__Sequence;
  using RosType = int64_t;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING> {
  using CppType = std::string;
  using SequenceType = rosidl_runtime_c__String__Sequence;
  using RosType = rosidl_runtime_c__String;
};

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING> {
  using CppType = std::u16string;
  using SequenceType = rosidl_runtime_c__U16String__Sequence;
  using RosType = rosidl_runtime_c__U16String;
};

template<int RosTypeId>
void write_member_item(
  const YAML::Node& yaml,
  uint8_t* buffer
) {
  using RosType = typename TypeMapping<RosTypeId>::RosType;
  RosType data = yaml.as<RosType>();
  *reinterpret_cast<RosType*>(buffer) = data;
}

template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>(
  const YAML::Node& yaml,
  uint8_t* buffer
) {
  using RosType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING>::RosType;
  RosType* ros_string =
    reinterpret_cast<RosType*>(buffer);
  std::string s = yaml.as<std::string>();
  ros_string->data = new char[s.size() + 1];
  strncpy(ros_string->data, s.data(), s.size() + 1);
  ros_string->size = s.size();
  ros_string->capacity = s.size() + 1;
}

template<>
void write_member_item<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>(
  const YAML::Node& yaml,
  uint8_t* buffer
) {
  using RosType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>::RosType;
  RosType* ros_string =
    reinterpret_cast<RosType*>(buffer);
  std::u16string u16s = string_to_u16string(yaml.as<std::string>());
  ros_string->data = new uint16_t[u16s.size() + 1];
  memcpy(ros_string->data, u16s.data(), (u16s.size() + 1) * sizeof(std::u16string::value_type));
  // should this be the length of chars or the number of bytes?
  ros_string->size = u16s.size();
  ros_string->capacity = u16s.size() + 1;
}

template<int RosTypeId>
void write_member_sequence(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  using SequenceType = typename TypeMapping<RosTypeId>::SequenceType;
  using RosType = typename TypeMapping<RosTypeId>::RosType;
  if (member.is_upper_bound_ && yaml.size() > member.array_size_) {
    throw std::runtime_error("yaml sequence is more than capacity");
  }
  auto seq = reinterpret_cast<SequenceType*>(buffer);
  seq->data = new RosType[yaml.size()];
  for (size_t i = 0; i < yaml.size(); i++) {
    write_member_item<RosTypeId>(
      yaml[i],
      reinterpret_cast<uint8_t*>(seq->data + i)
    );
  }
  seq->size = yaml.size();
  seq->capacity = yaml.size();
}

bool is_sequence(const MemberInfo& member) {
  if ((member.is_array_ && member.array_size_ == 0) || member.is_upper_bound_) {
    return true;
  }
  return false;
}

template<int RosTypeId>
void write_member(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  using RosType = typename TypeMapping<RosTypeId>::RosType;
  if (is_sequence(member)) {
    write_member_sequence<RosTypeId>(yaml[member.name_], buffer + member.offset_, member);
    return;
  }

  if (member.is_array_) {
    for (size_t i = 0; i < member.array_size_; i++) {
      write_member_item<RosTypeId>(
        yaml[member.name_][i],
        buffer + member.offset_ + sizeof(RosType) * i
      );
    }
  } else {
    write_member_item<RosTypeId>(yaml[member.name_], buffer + member.offset_);
  }
}

void write_member_sequence_nested(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  // We don't know the type at compiler time but they all follow the same structure.
  using SequenceType = rosidl_runtime_c__uint8__Sequence;
  using RosType = void*;

  if (member.is_upper_bound_ && yaml.size() > member.array_size_) {
    throw std::runtime_error("yaml sequence is more than capacity");
  }
  const TypeInfo* member_typeinfo = reinterpret_cast<const TypeInfo*>(member.members_->data);
  auto seq = reinterpret_cast<SequenceType*>(buffer);
  seq->data = new uint8_t[member_typeinfo->size_of_ * yaml.size()];
  for (size_t i = 0; i < yaml.size(); i++) {
    yaml_to_rosmsg_impl(yaml[i], member_typeinfo, seq->data + member_typeinfo->size_of_ * i);
  }
  seq->size = yaml.size();
  seq->capacity = yaml.size();
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
