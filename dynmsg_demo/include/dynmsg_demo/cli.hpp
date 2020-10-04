#ifndef CLI_HPP
#define CLI_HPP

#include <unordered_map>

enum class Command {
  Unknown,
  TopicEcho,
  TopicPublish,
  ServiceCall,
  ServiceHost,
};

struct Arguments {
  Command cmd;
  std::unordered_map<std::string, std::string> params;
};

Arguments parse_arguments(int argc, char** argv);

#endif
