#include "../src/string_utils.hpp"

#include <string>

#include <gtest/gtest.h>

using namespace std::string_literals;

TEST(WideStrings, StringToU16) {
  std::string utf8 = u8"z\u00df\u6c34\U0001d10b";  // "zß水𝄋"
  EXPECT_EQ(string_to_u16string(utf8), u"z\u00df\u6c34\U0001d10b"s);
}

TEST(WideStrings, U16ToString) {
  std::u16string u16 = u"z\u00df\u6c34\U0001d10b";  // "zß水𝄋"
  EXPECT_EQ(u16string_to_string(u16), u8"z\u00df\u6c34\U0001d10b"s);
}
