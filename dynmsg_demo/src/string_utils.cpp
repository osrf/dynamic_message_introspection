#include "string_utils.hpp"

#include <codecvt>
#include <locale>

std::u16string string_to_u16string(const std::string& input) {
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
  return converter.from_bytes(input);
}

std::string u16string_to_string(const std::u16string& input) {
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
  return converter.to_bytes(input);
}
