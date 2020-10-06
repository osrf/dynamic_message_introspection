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

// is there a better approach?
#define DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(type_name_enum, type_name) \
  const SequenceInitFunc< \
    TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_ ## type_name_enum>::SequenceType \
  > TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_ ## type_name_enum>::sequence_init \
    = rosidl_runtime_c__ ## type_name ## __Sequence__init

// forward declare
void yaml_to_rosmsg_impl(
  const YAML::Node& root,
  const TypeInfo* typeinfo,
  uint8_t* buffer
);

template<int RosTypeId>
struct TypeMapping {};

template<typename SequenceType>
using SequenceInitFunc = bool (*)(SequenceType*, size_t);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT> {
  using CppType = float;
  using SequenceType = rosidl_runtime_c__float32__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(FLOAT, float32);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE> {
  using CppType = double;
  using SequenceType = rosidl_runtime_c__double__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(DOUBLE, double);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE> {
  using CppType = long double;
  using SequenceType = rosidl_runtime_c__long_double__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(LONG_DOUBLE, long_double);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_CHAR> {
  using CppType = signed char;
  using SequenceType = rosidl_runtime_c__char__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(CHAR, char);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR> {
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__wchar__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(WCHAR, wchar);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN> {
  using CppType = bool;
  using SequenceType = rosidl_runtime_c__bool__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(BOOLEAN, bool);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_OCTET> {
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__octet__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(OCTET, octet);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT8> {
  using CppType = uint8_t;
  using SequenceType = rosidl_runtime_c__uint8__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(UINT8, uint8);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT8> {
  using CppType = int8_t;
  using SequenceType = rosidl_runtime_c__int8__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(INT8, int8);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT16> {
  using CppType = uint16_t;
  using SequenceType = rosidl_runtime_c__uint16__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(UINT16, uint16);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT16> {
  using CppType = int16_t;
  using SequenceType = rosidl_runtime_c__int16__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(INT16, int16);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT32> {
  using CppType = uint32_t;
  using SequenceType = rosidl_runtime_c__uint32__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(UINT32, uint32);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT32> {
  using CppType = int32_t;
  using SequenceType = rosidl_runtime_c__int32__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(INT32, int32);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_UINT64> {
  using CppType = uint64_t;
  using SequenceType = rosidl_runtime_c__uint64__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(UINT64, uint64);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_INT64> {
  using CppType = int64_t;
  using SequenceType = rosidl_runtime_c__int64__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(INT64, int64);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_STRING> {
  using CppType = rosidl_runtime_c__String;
  using SequenceType = rosidl_runtime_c__String__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(STRING, String);

template<>
struct TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING> {
  using CppType = rosidl_runtime_c__U16String;
  using SequenceType = rosidl_runtime_c__U16String__Sequence;
  static const SequenceInitFunc<SequenceType> sequence_init;
};
DYNMSG_DEMO_DECALRE_SEQUENCE_INIT_FUNC(WSTRING, U16String);

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
  CppType* ros_string = reinterpret_cast<CppType*>(buffer);
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
  using CppType = typename TypeMapping<rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING>::CppType;
  CppType* ros_string = reinterpret_cast<CppType*>(buffer);
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
  using CppType = typename TypeMapping<RosTypeId>::CppType;
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
  if ((member.is_array_ && member.array_size_ == 0) || member.is_upper_bound_) {
    return true;
  }
  return false;
}

template<int RosTypeId>
void write_member(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  using CppType = typename TypeMapping<RosTypeId>::CppType;
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
  // We don't know the type at compiler time but they all follow the same structure.
  using SequenceType = rosidl_runtime_c__uint8__Sequence;
  using CppType = void*;

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
