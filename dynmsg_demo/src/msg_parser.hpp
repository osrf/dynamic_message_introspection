#include "typesupport_utils.hpp"

#include <yaml-cpp/yaml.h>

#include <vector>

std::vector<uint8_t> yaml_to_rosmsg(const std::string& yaml_str, const TypeInfo* typeinfo);
