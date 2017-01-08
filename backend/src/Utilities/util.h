#ifndef UTIL
#define UTIL

#include <iostream>
#include <vector>
#include <sstream>
#include <glib.h>
#include <sqlite3.h>

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

  static void initialize();
 private:
  static void set_os_plat();
  static std::string get_home_dir();
  static void create_dir(std::string dir_location);
  static void init_db();
  static void load_db();
  static void scan_dir(const char *dir_location);
  static int generic_db_callback(void *data, int total_col_num, char **value, char **fields);
  static int  flush_to_db(sqlite3 *in_memory, const char *file_name);
};
#endif
