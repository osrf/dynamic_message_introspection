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

#include "dynmsg_demo/cli.hpp"

#include <cstring>
#include <iostream>
#include <string>


using namespace std::string_literals;

void print_help_and_exit(const char * program_name)
{
  std::cout << "Usage:\n"
            << "  " << program_name << " echo <topic>\n"
            << "  " << program_name << " publish <topic> <type> <message>\n"
            << "  " << program_name << " call <service> <request>\n"
            << "  " << program_name << " host <service> <response>\n"
            << "  " << program_name << " discover\n"
            << std::endl;
  exit(1);
}

Arguments parse_arguments(int argc, char ** argv)
{
  if (argc < 2 ||
    std::string(argv[1]).rfind("-h", 0) == 0 ||
    std::string(argv[1]).rfind("--help", 0) == 0)
  {
    print_help_and_exit(argv[0]);
  }
  Arguments args;
  args.cmd = Command::Unknown;

  if (argv[1] == "echo"s) {
    args.cmd = Command::TopicEcho;
    if (argc < 3) {
      print_help_and_exit(argv[0]);
    }
    args.params["topic"] = argv[2];
  } else if (argv[1] == "publish"s) {
    args.cmd = Command::TopicPublish;
    if (argc < 5) {
      print_help_and_exit(argv[0]);
    }
    args.params["topic"] = argv[2];
    args.params["type"] = argv[3];
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
  } else if (argv[1] == "discover"s) {
    args.cmd = Command::Discover;
  } else {
    print_help_and_exit(argv[0]);
  }

  return args;
}
