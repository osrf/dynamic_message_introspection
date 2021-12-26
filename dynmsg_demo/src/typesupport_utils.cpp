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

#include <dlfcn.h>

#include <sstream>
#include <string>

#include "dynmsg_demo/typesupport_utils.hpp"

#include "rcl/error_handling.h"
#include "rcl/graph.h"
#include "rcutils/logging_macros.h"

InterfaceTypeName get_topic_type(const rcl_node_t * node, const std::string & topic)
{
  auto pubs = rcl_get_zero_initialized_topic_endpoint_info_array();
  auto allocator = rcl_get_default_allocator();
  // Find a publisher for the requested topic
  auto ret = rcl_get_publishers_info_by_topic(node, &allocator, topic.data(), false, &pubs);
  if (ret != RCL_RET_OK) {
    throw std::runtime_error(rcl_get_error_string().str);
  }
  if (pubs.size == 0) {
    throw std::runtime_error("unable to determine topic type");
  }
  // Get the topic type from the graph information
  std::string topic_type(pubs.info_array->topic_type);
  std::string pkg = topic_type.substr(0, topic_type.find('/'));
  std::string name = topic_type.substr(topic_type.rfind('/') + 1);
  InterfaceTypeName int_type_name{pkg, name};

  // Clean up
  ret = rcl_topic_endpoint_info_array_fini(&pubs, &allocator);
  if (ret != RCL_RET_OK) {
    throw std::runtime_error(rcl_get_error_string().str);
  }
  return int_type_name;
}


InterfaceTypeName get_topic_type_from_string_type(const std::string & type)
{
  std::string::size_type split_at = type.find('/');
  if (split_at == std::string::npos) {
    throw std::runtime_error("invalid type specification");
  }
  return InterfaceTypeName(type.substr(0, split_at), type.substr(split_at + 1));
}

const TypeSupport * get_type_support(const InterfaceTypeName & interface_type)
{
  // Load the type support library for the package containing the requested type
  std::string ts_lib_name;
  ts_lib_name = "lib" + interface_type.first + "__rosidl_typesupport_c.so";
  RCUTILS_LOG_DEBUG_NAMED(
    "dynmsg_demo",
    "Loading type support library %s",
    ts_lib_name.c_str());
  void * type_support_lib = dlopen(ts_lib_name.c_str(), RTLD_LAZY);
  if (type_support_lib == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support library: %s", dlerror());
    return nullptr;
  }
  // Load the function that, when called, will give us the type support for the interface type we
  // are interested in
  std::string ts_func_name;
  ts_func_name = "rosidl_typesupport_c__get_message_type_support_handle__" + interface_type.first +
    "__msg__" + interface_type.second;
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loading type support function %s", ts_func_name.c_str());

  get_message_ts_func type_support_handle_func =
    reinterpret_cast<get_message_ts_func>(dlsym(type_support_lib, ts_func_name.c_str()));
  if (type_support_handle_func == nullptr) {
    RCUTILS_LOG_ERROR_NAMED("dynmsg_demo", "failed to load type support function: %s", dlerror());
    return nullptr;
  }

  // Call the function to get the type support we want
  const rosidl_message_type_support_t * ts = type_support_handle_func();
  RCUTILS_LOG_DEBUG_NAMED("dynmsg_demo", "Loaded type support %s", ts->typesupport_identifier);

  return ts;
}
