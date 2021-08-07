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

#include <gtest/gtest.h>

#include <string>

#include "dynmsg/string_utils.hpp"

using namespace std::string_literals;

TEST(WideStrings, StringToU16) {
  std::string utf8 = u8"z\u00df\u6c34\U0001d10b";  // "zß水𝄋"
  EXPECT_EQ(string_to_u16string(utf8), u"z\u00df\u6c34\U0001d10b"s);
}

TEST(WideStrings, U16ToString) {
  std::u16string u16 = u"z\u00df\u6c34\U0001d10b";  // "zß水𝄋"
  EXPECT_EQ(u16string_to_string(u16), u8"z\u00df\u6c34\U0001d10b"s);
}
