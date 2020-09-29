#include <dlfcn.h>
#include <unistd.h>

#include <clocale>
#include <iostream>
#include <locale>
#include <memory>
#include <sstream>
#include <vector>

#include "rcl/context.h"
#include "rcl/init_options.h"
#include "rcl/node_options.h"
#include "rcl/node.h"
#include "rcl/rcl.h"
#include "rcl/subscription.h"
#include "rcl/types.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_c/field_types.h"

#include "rcutils/logging_macros.h"

void
message_to_string(
  const rosidl_typesupport_introspection_c__MessageMembers * type_info,
  std::shared_ptr<uint8_t> message_data,
  size_t indent_level,
  std::stringstream &output);


std::string
widestring_to_string(std::u16string * input)
{
  std::setlocale(LC_ALL, "");
  const std::locale locale("");
  typedef std::codecvt<char16_t, char, std::mbstate_t> converter_type;
  const converter_type &converter = std::use_facet<converter_type>(locale);
  std::vector<char> to; to = std::vector<char>(input->length() * converter.max_length());
  std::mbstate_t state;
  const char16_t * from_next;
  char * to_next;
  const converter_type::result result = converter.out(
    state,
    input->data(),
    input->data() + input->length(),
    from_next,
    &to[0],
    &to[0] + to.size(),
    to_next);
  if (result == converter_type::ok or result == converter_type::noconv) {
    const std::string s(&to[0], to_next);
    return s;
  } else {
    return "failed to convert u16string";
  }
}

const char *
member_type_to_string(const rosidl_typesupport_introspection_c__MessageMember &type_info)
{
  switch (type_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      return "float";
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      return "double";
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      return "long double";
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      return "char";
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      return "wchar";
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      return "boolean";
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      return "octet";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      return "uint8";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      return "int8";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      return "uint16";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      return "int16";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      return "uint32";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      return "int32";
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      return "uint64";
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      return "int64";
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      return "string";
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      return "wstring";
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      return "message";
    default:
      return "UNKNOWN";
  }
}


std::string
member_value_to_string(
  const rosidl_typesupport_introspection_c__MessageMember &type_info,
  std::shared_ptr<uint8_t> message_data)
{
  std::stringstream value;
  switch (type_info.type_id_) {
    case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
      value << *reinterpret_cast<float*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
      value << *reinterpret_cast<double*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_LONG_DOUBLE:
      value << *reinterpret_cast<long double*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_CHAR:
      value << *reinterpret_cast<unsigned char*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WCHAR:
      value << *reinterpret_cast<char16_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN:
      value << *reinterpret_cast<bool*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_OCTET:
      value << *reinterpret_cast<unsigned char*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
      value << *reinterpret_cast<uint8_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
      value << *reinterpret_cast<int8_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
      value << *reinterpret_cast<uint16_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
      value << *reinterpret_cast<int16_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
      value << *reinterpret_cast<uint32_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
      value << *reinterpret_cast<int32_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
      value << *reinterpret_cast<uint64_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
      value << *reinterpret_cast<int64_t*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
      value << *reinterpret_cast<std::string*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_WSTRING:
      value << widestring_to_string(
        reinterpret_cast<std::u16string*>(&message_data.get()[type_info.offset_]));
      //value << *reinterpret_cast<std::u16string*>(&message_data.get()[type_info.offset_]);
      break;
    case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
      value << "recursively handle sub-message here";
      break;
    default:
      value << "unknown value for unknown type";
      break;
  }
  return value.str();
}


void add_indent(size_t indent_level, std::stringstream &output)
{
  for (size_t ii = 0; ii < indent_level; ++ii) {
    output << "  ";
  }
}


void member_to_string(
  const rosidl_typesupport_introspection_c__MessageMember &member_info,
  std::shared_ptr<uint8_t> message_data,
  size_t indent_level,
  std::stringstream &output)
{
  if (member_info.type_id_ == rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE) {
    // Nested message member
    const rosidl_typesupport_introspection_c__MessageMembers * nested_type_info =
      reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
        member_info.members_->data);
    add_indent(indent_level, output);
    output << member_info.name_ << " (" << nested_type_info->message_namespace_ <<
      '/' << nested_type_info->message_name_ << "):\n";
    message_to_string(
      nested_type_info,
      std::shared_ptr<uint8_t>(message_data, message_data.get() + member_info.offset_),
      indent_level + 1,
      output);
  } else {
    // POD member
    add_indent(indent_level, output);
    output << member_info.name_ << " (" <<
      member_type_to_string(member_info) << "):\t" <<
      member_value_to_string(member_info, message_data) << '\n';
  }
}


void message_to_string(
  const rosidl_typesupport_introspection_c__MessageMembers * type_info,
  std::shared_ptr<uint8_t> message_data,
  size_t indent_level,
  std::stringstream &output)
{
  for (uint32_t ii = 0; ii < type_info->member_count_; ++ii) {
    member_to_string(type_info->members_[ii], message_data, indent_level, output);
  }
}


typedef struct TypeSupport
{
  void * type_support_library;
  const rosidl_message_type_support_t * type_support;
  void * introspection_library;
  const rosidl_message_type_support_t * introspection;
  const rosidl_typesupport_introspection_c__MessageMembers * type_info;
} TypeSupport;


rcl_ret_t load_interface_type_support(
  const std::string &namespace_,
  const std::string &interface,
  TypeSupport &type_support)
{
  std::string ts_lib_name;
  ts_lib_name = "lib" + namespace_ + "__rosidl_typesupport_c.so";
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support library %s", ts_lib_name.c_str());
  type_support.type_support_library = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support.type_support_library == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support library: %s", dlerror());
    return RCL_RET_ERROR;
  }
  std::string ts_func_name;
  ts_func_name = "rosidl_typesupport_c__get_message_type_support_handle__" + namespace_ +
    "__msg__" + interface;
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading type support function %s",
    ts_func_name.c_str());
  typedef const rosidl_message_type_support_t* (*get_interface_ts_func)();
  get_interface_ts_func type_support_handle_func = reinterpret_cast<get_interface_ts_func>(dlsym(
    type_support.type_support_library,
    ts_func_name.c_str()));
  if (type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support function: %s", dlerror());
    return RCL_RET_ERROR;
  }
  type_support.type_support = type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    type_support.type_support->typesupport_identifier);

  ts_lib_name = "lib" + namespace_ + "__rosidl_typesupport_introspection_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading introspection type support library %s",
    ts_lib_name.c_str());
  type_support.introspection_library = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support.introspection_library == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg_demo",
      "failed to load introspection type support library: %s",
      dlerror());
    return RCL_RET_ERROR;
  }
  ts_func_name = "rosidl_typesupport_introspection_c__get_message_type_support_handle__" +
    namespace_ + "__msg__" + interface;
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.c_str());
  get_interface_ts_func introspection_type_support_handle_func =
    reinterpret_cast<get_interface_ts_func>(dlsym(
      type_support.introspection_library,
      ts_func_name.c_str()));
  if (type_support.introspection_library == nullptr) {
    RCUTILS_LOG_ERROR_NAMED(
      "dynmsg_demo",
      "failed to load introspection type support function: %s",
      dlerror());
    return RCL_RET_ERROR;
  }
  type_support.introspection = introspection_type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loaded type support %s",
    type_support.introspection->typesupport_identifier);
  type_support.type_info =
    reinterpret_cast<const rosidl_typesupport_introspection_c__MessageMembers *>(
      type_support.introspection->data);

  return RCL_RET_OK;
}


int
main(int argc, char ** argv) {
  std::string msg_namespace(argv[1]);
  std::string msg_type(argv[2]);

  rcl_init_options_t options = rcl_get_zero_initialized_init_options();
  rcl_ret_t ret = rcl_init_options_init(&options, rcl_get_default_allocator());
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init options failed");
    return 1;
  }

  rcl_context_t context = rcl_get_zero_initialized_context();
  ret = rcl_init(argc, argv, &options, &context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init failed");
    return 1;
  }
  ret = rcl_init_options_fini(&options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "init_options fini failed");
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating node");
  rcl_node_options_t node_options = rcl_node_get_default_options();
  rcl_node_t node = rcl_get_zero_initialized_node();
  ret = rcl_node_init(&node, "dynmsg_test", "", &context, &node_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node init failed");
    return 1;
  }

  TypeSupport type_support;
  if (load_interface_type_support(msg_namespace, msg_type, type_support) != RCL_RET_OK) {
    // Error message already printed
    return 1;
  }

  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Creating subscription");
  rcl_subscription_t sub = rcl_get_zero_initialized_subscription();
  rcl_subscription_options_t sub_options = rcl_subscription_get_default_options();
  ret = rcl_subscription_init(&sub, &node, type_support.type_support, "dynmsg", &sub_options);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "subscription init failed");
    return 1;
  }

  bool running = true;
  while (running) {
    size_t count{0};
    ret = rmw_subscription_count_matched_publishers(rcl_subscription_get_rmw_handle(&sub), &count);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "pub count failed");
      return 1;
    }
    RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "There are %ld matched publishers", count);
    if (count > 0) {
      break;
    }
    sleep(0.25);
  }

  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Allocating message buffer of size %ld bytes",
    type_support.type_info->size_of_);
  std::shared_ptr<uint8_t> message(
    new uint8_t[type_support.type_info->size_of_],
    std::default_delete<uint8_t[]>());

  bool taken = false;
  while (!taken) {
    taken = false;
    ret = rmw_take(rcl_subscription_get_rmw_handle(&sub), message.get(), &taken, nullptr);
    if (ret != RCL_RET_OK) {
      RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "take failed");
      return 1;
    }
    if (taken) {
      RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Received data");
      break;
    }
  }

  std::stringstream output;
  output << type_support.type_info->message_namespace_ << '/' <<
    type_support.type_info->message_name_ << '\n';
  message_to_string(type_support.type_info, message, 1, output);
  std::cout << output.str();

  ret = rcl_node_fini(&node);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "node fini failed");
    return 1;
  }
  ret = rcl_shutdown(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "shutdown failed");
    return 1;
  }
  ret = rcl_context_fini(&context);
  if (ret != RCL_RET_OK) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "context fini failed");
    return 1;
  }
  return 0;
}
