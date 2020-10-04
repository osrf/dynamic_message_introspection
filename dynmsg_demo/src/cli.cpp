#include "dynmsg_demo/cli.hpp"

#include <iostream>
#include <string>


using namespace std::string_literals;

void print_help_and_exit(const char * program_name) {
  std::cout << "Usage:\n"
    << "  " << program_name << " echo <topic> <message_type>\n"
    << "  " << program_name << " publish <topic> <message_type> <message>\n"
    << "  " << program_name << " call <service> <request>\n"
    << "  " << program_name << " host <service> <response>\n"
    << std::endl;
  exit(1);
}

Arguments parse_arguments(int argc, char** argv) {
  if (argc < 2 ||
      std::string(argv[1]).rfind("-h", 0) == 0 ||
      std::string(argv[1]).rfind("--help", 0) == 0
  ) {
    print_help_and_exit(argv[0]);
  }
  Arguments args;
  args.cmd = Command::Unknown;

  if (argv[1] == "echo"s) {
    args.cmd = Command::TopicEcho;
    if (argc < 4) {
      print_help_and_exit(argv[0]);
    }
    args.params["topic"] = argv[2];
    args.params["message_type"] = argv[3];
  } else if (argv[1] == "publish"s) {
    args.cmd = Command::TopicPublish;
    if (argc < 5) {
      print_help_and_exit(argv[0]);
    }
    args.params["topic"] = argv[2];
    args.params["message_type"] = argv[3];
    args.params["msg"] = argv[4];
  } else if (argv[1] == "call"s) {
    args.cmd = Command::ServiceCall;
    if (argc < 4) {
      print_help_and_exit(argv[0]);
    }
    args.params["service"] = argv[2];
    args.params["req"] = argv[3];
  } else if (argv[1] == "host"s) {
    args.cmd = Command::ServiceHost;
    if (argc < 4) {
      print_help_and_exit(argv[0]);
    }
    args.params["service"] = argv[2];
    args.params["resp"] = argv[3];
  } else {
    print_help_and_exit(argv[0]);
  }

  return args;
}
