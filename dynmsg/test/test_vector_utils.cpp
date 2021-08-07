// Copyright 2021 Christophe Bedard
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
#include <vector>

#include "dynmsg/vector_utils.hpp"

struct some_custom_object
{
  std::string str;
  int i;
  double d;
  float f;
};

template<typename T>
size_t _get_vector_size(std::vector<T> & vector)
{
  return dynmsg::get_vector_size(reinterpret_cast<uint8_t *>(&vector), sizeof(T));
}

TEST(TestVectorUtils, get_vector_size)
{
  std::vector<std::string> vector_string;
  vector_string.push_back("abcdef");
  vector_string.push_back("hijklmnop");
  vector_string.push_back("qrstuv");
  vector_string.push_back("xyz");
  vector_string.push_back("1234567890");
  vector_string.push_back("09876543211234567890");
  EXPECT_EQ(6ul, _get_vector_size(vector_string));

  std::vector<int> vector_int;
  vector_int.push_back(-4);
  vector_int.push_back(20);
  vector_int.push_back(6);
  vector_int.push_back(9);
  EXPECT_EQ(4ul, _get_vector_size(vector_int));

  std::vector<some_custom_object> vector_custom;
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  vector_custom.push_back({});
  EXPECT_EQ(9ul, _get_vector_size(vector_custom));

  // Special case, but it shouldn't happen
  std::vector<void *> vector_void;
  EXPECT_EQ(0ul, _get_vector_size(vector_void));
}
