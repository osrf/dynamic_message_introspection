#include "dynmsg_demo/cli.hpp"

#include <iostream>
#include <string>


using namespace std::string_literals;

void print_help_and_exit() {
  std::cout << "Usage:\n"
    << "  dynmsg echo <topic>\n"
    << "  dynmsg publish <topic> <message>\n"
    << "  dynmsg call <service> <request>\n"
    << "  dynmsg host <service> <response>\n"
    << std::endl;
  exit(1);
}

Arguments parse_arguments(int argc, char** argv) {
  if (argc < 2 ||
      std::string(argv[1]).rfind("-h", 0) == 0 ||
      std::string(argv[1]).rfind("--help", 0) == 0
  ) {
    print_help_and_exit();
  }
  Arguments args;
  args.cmd = Command::Unknown;

  std::unordered_map<std::string, std::string> params;
  if (argv[1] == "echo"s) {
    args.cmd = Command::TopicEcho;
    if (argc < 3) {
      print_help_and_exit();
    }
    params["topic"] = argv[2];
  } else if (argv[1] == "publish"s) {
    args.cmd = Command::TopicPublish;
    if (argc < 4) {
      print_help_and_exit();
    }
    params["topic"] = argv[2];
    params["msg"] = argv[3];
  } else if (argv[1] == "call"s) {
    args.cmd = Command::ServiceCall;
    if (argc < 4) {
      print_help_and_exit();
    }
    params["service"] = argv[2];
    params["req"] = argv[3];
  } else if (argv[1] == "host"s) {
    args.cmd = Command::ServiceHost;
    if (argc < 4) {
      print_help_and_exit();
    }
    params["service"] = argv[2];
    params["resp"] = argv[3];
  }

  return args;
}
