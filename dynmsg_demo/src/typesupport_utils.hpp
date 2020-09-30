#ifndef TYPESUPPORT_UTILS_HPP
#define TYPESUPPORT_UTILS_HPP

#include <rosidl_typesupport_introspection_c/message_introspection.h>

#include <string>

using TypeInfo = rosidl_typesupport_introspection_c__MessageMembers;
using MemberInfo = rosidl_typesupport_introspection_c__MessageMember;

// TODO: export this?
const TypeInfo* get_type_info(const std::string& msg_namespace, const std::string& msg_type);

/**
 * Wrapper to a generic ros message
 * */
extern "C"
typedef struct RosMessage {
  const TypeInfo* type_info;
  uint8_t* data;
} RosMessage;

extern "C"
int ros_message_init(
  const char* msg_namespace,
  const char* msg_type,
  RosMessage* ros_msg
);

extern "C"
int ros_message_destroy(RosMessage* ros_msg);

#endif
