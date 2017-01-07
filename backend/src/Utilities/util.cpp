#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <Utilities/util.h>

namespace {
  std::vector<std::string> subdir_locations;
  std::vector<std::string> file_locations;
  int total_files=0;
  int subdir_count=0;
};

void util::scan_dir(const char *dir_location){

  subdir_locations.push_back(dir_location);

  for (size_t subdir_iter = 0; subdir_iter < subdir_locations.size(); subdir_iter++){
    std::string file_location = subdir_locations[subdir_iter];
    if (file_location.substr(file_location.length() - 1) != "/")
      file_location += "/";

    GError *error = NULL;
    GError *subdir_error = NULL;

    std::stringstream test;
    const char *file;
    GDir *dir = g_dir_open(subdir_locations[subdir_iter].c_str(), 0, &error);

    while ((file = g_dir_read_name(dir))){
      try {
        GError *subdir_error = NULL;

        std::string subdir_location = file_location + file;
        g_dir_open(util::to_char(subdir_location), 0, &subdir_error);
        if (subdir_error == NULL) {
          subdir_count++;
          subdir_locations.push_back(util::to_char(subdir_location));
        }
        if (subdir_error != NULL){
          throw 0;
        }
      }
      catch (int exception)
        {
          std::string temp = file_location;
          file_location += file;
          std::cout << "File loc -> " << file_location << std::endl;

          // check file format here
          total_files++;
          file_locations.push_back(file_location);

          file_location = temp;
        }
    }
  }
  std::cout << "No. of Files : " << total_files << std::endl;
  std::cout << "No. of Subdirectories : " << subdir_count << std::endl;
  //sqlite3 *library_db = library_db;
}

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

