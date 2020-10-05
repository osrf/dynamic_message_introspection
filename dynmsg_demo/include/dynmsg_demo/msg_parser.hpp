#ifndef MSG_PARSER_HPP
#define MSG_PARSER_HPP

#include "typesupport_utils.hpp"

#include <vector>

RosMessage yaml_to_rosmsg(const InterfaceTypeName &interface_type, const std::string& yaml_str);

#endif
