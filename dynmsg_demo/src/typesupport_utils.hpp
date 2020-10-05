#ifndef TYPESUPPORT_UTILS_HPP
#define TYPESUPPORT_UTILS_HPP


#include <string>

#include <rcl/types.h>
#include <rosidl_typesupport_introspection_c/message_introspection.h>

using TypeSupport = rosidl_message_type_support_t;
using TypeInfo = rosidl_typesupport_introspection_c__MessageMembers;
using MemberInfo = rosidl_typesupport_introspection_c__MessageMember;

// TODO: export this?
const TypeSupport* get_type_support(const std::string& msg_namespace, const std::string& msg_type);
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
rcl_ret_t ros_message_init(
  const char* msg_namespace,
  const char* msg_type,
  RosMessage* ros_msg
);

extern "C"
void ros_message_destroy(RosMessage* ros_msg);

#endif
