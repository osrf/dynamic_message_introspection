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

#ifndef DYNMSG_DEMO__CLI_HPP_
#define DYNMSG_DEMO__CLI_HPP_

#include <string>
#include <unordered_map>

// Commands available in the CLI tool
enum class Command
{
  Unknown,
  TopicEcho,
  TopicPublish,
  ServiceCall,
  ServiceHost,
  Discover,
};

struct Arguments
{
  Command cmd;
  std::unordered_map<std::string, std::string> params;
};

// Parse the arguments given on the command line into a command and its arguments.
// Some simple error checking is performed only.
Arguments parse_arguments(int argc, char ** argv);

#endif  // DYNMSG_DEMO__CLI_HPP_
