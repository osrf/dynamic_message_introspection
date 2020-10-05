#ifndef TYPESUPPORT_UTILS_HPP
#define TYPESUPPORT_UTILS_HPP


#include <utility>
#include <string>

#include <rcl/types.h>
#include <rosidl_typesupport_introspection_c/message_introspection.h>

// forward declare
struct rcl_node_t;

using TypeSupport = rosidl_message_type_support_t;
using TypeInfo = rosidl_typesupport_introspection_c__MessageMembers;
using MemberInfo = rosidl_typesupport_introspection_c__MessageMember;

using InterfaceTypeName = std::pair<std::string, std::string>;

InterfaceTypeName get_topic_type(const rcl_node_t *node, const std::string &topic);

// TODO: export this?
const TypeSupport* get_type_support(const InterfaceTypeName &interface_type);
const TypeInfo* get_type_info(const InterfaceTypeName &interface_type);

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
  const InterfaceTypeName &interface_type,
  RosMessage* ros_msg
);

extern "C"
void ros_message_destroy(RosMessage* ros_msg);

#endif
