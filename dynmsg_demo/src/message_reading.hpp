#ifndef DYNMSG_DEMO_SRC_MESSAGE_READING_HPP_
#define DYNMSG_DEMO_SRC_MESSAGE_READING_HPP_

#include <yaml-cpp/yaml.h>

// Forward declarations
struct RosMessage;

YAML::Node message_to_yaml(const RosMessage &message);

#endif  // DYNMSG_DEMO_SRC_MESSAGE_READING_HPP_
