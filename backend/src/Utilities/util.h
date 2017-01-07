#ifndef UTIL
#define UTIL

#include <iostream>
#include <vector>
#include <sstream>

class util{
 public:
  static std::string replace(std::string text, std::string find_value, std::string replace_value);
  static std::string escape_string(std::string text);
  static std::string escape_spaces(std::string text);
  static std::string escape_slashes(std::string text);

  static bool has_text(std::string base_string, std::string search_value);
  static bool check_file_format(std::string file, std::string file_format);
  static char *to_char(std::string string_value);
  static int to_int (std::string text);

  template<class T>
    static std::string to_string(T input) {
    std::stringstream conv_stream;
    conv_stream << input;
    return conv_stream.str();
  }
};
#endif
