#ifndef MSG_PARSER_HPP
#define MSG_PARSER_HPP

#include "typesupport_utils.hpp"

#include <vector>

RosMessage yaml_to_rosmsg(
  const std::string& yaml_str,
  const std::string& msg_namespace,
  const std::string& msg_type
);

#endif
