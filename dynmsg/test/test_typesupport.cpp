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

#include "dynmsg/typesupport.hpp"

TEST(TestTypesupport, c)
{
  const TypeInfo * info = dynmsg::c::get_type_info({"std_msgs", "String"});
  EXPECT_NE(nullptr, info);
  const TypeInfo * info_bad = dynmsg::c::get_type_info({"super_msgs", "SuperRealMsg"});
  EXPECT_EQ(nullptr, info_bad);
}

TEST(TestTypesupport, cpp)
{
  const TypeInfo_Cpp * info = dynmsg::cpp::get_type_info({"std_msgs", "String"});
  EXPECT_NE(nullptr, info);
  const TypeInfo_Cpp * info_bad = dynmsg::cpp::get_type_info({"super_msgs", "SuperRealMsg"});
  EXPECT_EQ(nullptr, info_bad);
}
