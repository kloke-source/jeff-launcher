#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <Utilities/util.h>

std::string util::replace(std::string text, std::string find_value, std::string replace_value)
{
  std::stringstream replaced_text;
  for (size_t iter = 0; iter < text.size(); iter++){
    if (text[iter] != *util::to_char(find_value))
      replaced_text << text[iter];
    else
      replaced_text << replace_value;
  }
  return replaced_text.str();
}

std::string util::escape_string(std::string text)
{
  text = util::replace(text, "'", "''");
  return text;
}

std::string util::escape_spaces(std::string text)
{
  text = util::replace(text, " ", "\\ ");
  return text;
}

std::string util::escape_slashes(std::string text)
{
  text = util::replace(text, "/", "-");
  return text;
}

bool util::has_text(std::string base_string, std::string search_value)
{
  if (base_string.find(search_value) != std::string::npos)
    return true;
  else
    return false;
}

bool util::check_file_format(std::string file, std::string file_format)
{
  if (file.substr(file.find_last_of(".") + 1) == file_format)
    return true;
  else return false;
}

char* util::to_char(std::string string_value)
{
  std::string conv_string_value = (std::string) string_value;
  char *char_value = new char[conv_string_value.size() + 1];
  memcpy(char_value, conv_string_value.c_str(), conv_string_value.size() + 1);
  return char_value;
}

int util::to_int(std::string text)
{
  int value = atoi(text.c_str());
  return value;
}

