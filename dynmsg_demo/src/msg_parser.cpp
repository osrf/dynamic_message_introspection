#include "msg_parser.hpp"

#include <rosidl_runtime_c/string.h>
#include <rosidl_runtime_c/u16string.h>
#include <rosidl_typesupport_introspection_c/field_types.h>
#include <rcutils/logging_macros.h>

void yaml_to_rosmsg_impl(
  const YAML::Node& root,
  const MemberInfo& member,
  uint8_t* buffer
) {
  if (!root[member.name_]) {
    throw std::runtime_error("missing field \"" + std::string(member.name_) + "\"");
  }

  switch (member.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT: {
      float float_data = root[member.name_].as<float>();
      memcpy(buffer + member.offset_, &float_data, sizeof(float));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE: {
      double double_data = root[member.name_].as<double>();
      memcpy(buffer + member.offset_, &double_data, sizeof(double));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE: {
      long double ldouble_data = root[member.name_].as<long double>();
      memcpy(buffer + member.offset_, &ldouble_data, sizeof(long double));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR: {
      char char_data = root[member.name_].as<char>();
      memcpy(buffer + member.offset_, &char_data, sizeof(char));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR: {
      throw std::runtime_error("not implemented");
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN: {
      bool bool_data = root[member.name_].as<bool>();
      memcpy(buffer + member.offset_, &bool_data, sizeof(bool));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET: {
      uint8_t octet_data = root[member.name_].as<uint8_t>();
      memcpy(buffer + member.offset_, &octet_data, sizeof(uint8_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8: {
      uint8_t uint8_t_data = root[member.name_].as<uint8_t>();
      memcpy(buffer + member.offset_, &uint8_t_data, sizeof(uint8_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8: {
      int8_t int8_t_data = root[member.name_].as<int8_t>();
      memcpy(buffer + member.offset_, &int8_t_data, sizeof(int8_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16: {
      uint16_t uint16_t_data = root[member.name_].as<uint16_t>();
      memcpy(buffer + member.offset_, &uint16_t_data, sizeof(uint16_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16: {
      int16_t int16_t_data = root[member.name_].as<int16_t>();
      memcpy(buffer + member.offset_, &int16_t_data, sizeof(int16_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32: {
      uint32_t uint32_t_data = root[member.name_].as<uint32_t>();
      memcpy(buffer + member.offset_, &uint32_t_data, sizeof(uint32_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32: {
      int32_t int32_t_data = root[member.name_].as<int32_t>();
      memcpy(buffer + member.offset_, &int32_t_data, sizeof(int32_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64: {
      uint64_t uint64_t_data = root[member.name_].as<uint64_t>();
      memcpy(buffer + member.offset_, &uint64_t_data, sizeof(uint64_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64: {
      int64_t int64_t_data = root[member.name_].as<int64_t>();
      memcpy(buffer + member.offset_, &int64_t_data, sizeof(int64_t));
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING: {
      rosidl_runtime_c__String* ros_string =
        reinterpret_cast<rosidl_runtime_c__String*>(buffer + member.offset_);
      std::string s = root[member.name_].as<std::string>();
      ros_string->data = new char[s.size() + 1];
      strncpy(ros_string->data, s.data(), s.size() + 1);
      ros_string->size = s.size();
      ros_string->capacity = s.size() + 1;
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING: {
      throw std::runtime_error("not implemented");
      break;
    }
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE: {
      throw std::runtime_error("not implemented");
      break;
    }
    default: {
      throw std::runtime_error("unknown type");
    }
  }
}

std::vector<uint8_t> yaml_to_rosmsg(const std::string& yaml_str, const TypeInfo* typeinfo) {
  YAML::Node root = YAML::Load(yaml_str);
  std::vector<uint8_t> buffer(typeinfo->size_of_);
  for (uint32_t i = 0; i < typeinfo->member_count_; i++) {
    const auto& member = typeinfo->members_[i];
    yaml_to_rosmsg_impl(root, member, buffer.data());
  }
  return buffer;
}
