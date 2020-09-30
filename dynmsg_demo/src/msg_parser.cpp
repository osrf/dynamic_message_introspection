#include "msg_parser.hpp"
#include "string_utils.hpp"

#include <yaml-cpp/yaml.h>

#include <rosidl_runtime_c/string.h>
#include <rosidl_runtime_c/u16string.h>
#include <rosidl_typesupport_introspection_c/field_types.h>
#include <rcutils/logging_macros.h>

template<typename T>
void write_member(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  if (member.is_array_) {
    std::vector<T> sequence = yaml[member.name_].as<std::vector<T>>();
    for (size_t i = 0; i < member.array_size_; i++) {
      *reinterpret_cast<T*>(buffer + member.offset_ + sizeof(T) * i) = sequence[i];
    }
  } else {
    T data = yaml[member.name_].as<T>();
    *reinterpret_cast<T*>(buffer + member.offset_) = data;
  }
}

template<>
void write_member<std::string>(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  if (member.is_array_) {
    std::vector<std::string> sequence = yaml[member.name_].as<std::vector<std::string>>();
    for (size_t i = 0; i < member.array_size_; i++) {
      rosidl_runtime_c__String* ros_string =
        reinterpret_cast<rosidl_runtime_c__String*>(buffer + member.offset_ + sizeof(*ros_string) * i);
      ros_string->data = new char[sequence[i].size() + 1];
      strncpy(ros_string->data, sequence[i].data(), sequence[i].size() + 1);
      ros_string->size = sequence[i].size();
      ros_string->capacity = sequence[i].size() + 1;
    }
  } else {
    rosidl_runtime_c__String* ros_string =
      reinterpret_cast<rosidl_runtime_c__String*>(buffer + member.offset_);
    std::string s = yaml[member.name_].as<std::string>();
    ros_string->data = new char[s.size() + 1];
    strncpy(ros_string->data, s.data(), s.size() + 1);
    ros_string->size = s.size();
    ros_string->capacity = s.size() + 1;
  }
}

template<>
void write_member<std::u16string>(const YAML::Node& yaml, uint8_t* buffer, const MemberInfo& member) {
  if (member.is_array_) {
    std::vector<std::string> sequence = yaml[member.name_].as<std::vector<std::string>>();
    for (size_t i = 0; i < member.array_size_; i++) {
      rosidl_runtime_c__U16String* ros_string =
        reinterpret_cast<rosidl_runtime_c__U16String*>(buffer + member.offset_ + sizeof(*ros_string) * i);
      ros_string->data = new uint16_t[sequence[i].size() + 1];
      auto u16s = string_to_u16string(sequence[i]);
      memcpy(ros_string->data, u16s.data(), (u16s.size() + 1) * sizeof(std::u16string::value_type));
      // should this be the length of chars or the number of bytes?
      ros_string->size = u16s.size() * sizeof(std::u16string::value_type);
      ros_string->capacity = (u16s.size() + 1) * sizeof(std::u16string::value_type);
    }
  } else {
    rosidl_runtime_c__U16String* ros_string =
      reinterpret_cast<rosidl_runtime_c__U16String*>(buffer + member.offset_);
    std::u16string u16s = string_to_u16string(yaml[member.name_].as<std::string>());
    memcpy(ros_string->data, u16s.data(), (u16s.size() + 1) * sizeof(std::u16string::value_type));
    // should this be the length of chars or the number of bytes?
    ros_string->size = u16s.size() * sizeof(std::u16string::value_type);
    ros_string->capacity = (u16s.size() + 1) * sizeof(std::u16string::value_type);
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
        write_member<float>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE: {
        write_member<double>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE: {
        write_member<long double>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR: {
        write_member<char>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR: {
        write_member<uint16_t>(root, buffer, member);
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN: {
        write_member<bool>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET: {
        write_member<uint8_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8: {
        write_member<uint8_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT8: {
        write_member<int8_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16: {
        write_member<uint16_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT16: {
        write_member<int16_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32: {
        write_member<uint32_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT32: {
        write_member<int32_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64: {
        write_member<uint64_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_INT64: {
        write_member<int64_t>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_STRING: {
        write_member<std::string>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING: {
        write_member<std::u16string>(root, buffer, member);
        break;
      }
      case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE: {
        if (member.is_array_) {
          const TypeInfo* member_typeinfo = reinterpret_cast<const TypeInfo*>(member.members_->data);
          for (size_t i = 0; i < member.array_size_; i++) {
            yaml_to_rosmsg_impl(root[member.name_][i], member_typeinfo, buffer + member.offset_ + member_typeinfo->size_of_ * i);
          }
        } else {
          const TypeInfo* member_typeinfo = reinterpret_cast<const TypeInfo*>(member.members_->data);
          yaml_to_rosmsg_impl(root[member.name_], member_typeinfo, buffer + member.offset_);
        }
        break;
      }
      default: {
        throw std::runtime_error("unknown type");
      }
    }
  }
}

RosMessage yaml_to_rosmsg(
  const std::string& yaml_str,
  const std::string& msg_namespace,
  const std::string& msg_type
) {
  YAML::Node root = YAML::Load(yaml_str);
  RosMessage ros_msg;
  ros_message_init(msg_namespace.data(), msg_type.data(), &ros_msg);
  yaml_to_rosmsg_impl(root, ros_msg.type_info, ros_msg.data);
  return ros_msg;
}
