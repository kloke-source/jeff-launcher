#include <sstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <Utilities/util.h>
#include <sqlite3.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <Utilities/btree.h>
#include <Utilities/dir-indexer.h>
#include <functional>


enum {
  LINUX_PLAT,
  MAC_PLAT
};

namespace {
  std::vector<std::string> subdir_locations;
  std::vector<std::string> file_locations;

  int total_files=0;
  int subdir_count=0;

  int OS_TYPE;

  bool db_initialized=false;
  bool db_loaded=false;
  bool db_opened=false;

  std::string default_db_location;

  sqlite3 *index_db;


};

int util::get_os_plat()
{
  return OS_TYPE;
}

void util::set_os_plat()
{
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
  OS_TYPE = MAC_PLAT;
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
  // linux
  OS_TYPE = LINUX_PLAT;
#else
#   error "Unknown compiler"
#endif
}

std::string util::get_file_format(std::string file)
{
  return file.substr(file.find_last_of(".") + 1);
}

std::string util::get_home_dir()
{
  const char* home_dir = getenv("HOME");
  return util::to_string(home_dir);
}

void util::create_dir(std::string dir_location)
{
  std::string dir_cmd = "mkdir -pv " + dir_location;
#if defined(_WIN32)
  _mkdir(dir_location.c_str());
#else
  system(dir_cmd.c_str());
#endif
}

void util::initialize()
{
  util::set_os_plat();
  util::create_dir(util::get_home_dir() + "/.jeff-launcher");
  util::create_dir(util::get_home_dir() + "/.jeff-launcher/AppIcons");
  util::create_dir(util::get_home_dir() + "/.jeff-launcher/DatabaseIndex");

  default_db_location = util::get_home_dir() + "/.jeff-launcher/DatabaseIndex/index.db";

  util::init_db();

  if (OS_TYPE == MAC_PLAT)
  DirIndex::search("/", "Applications");



    util::flush_to_db(index_db, default_db_location.c_str());
}

std::string util::get_plist_property(std::string plist_prop, std::string plist_loc)
{
  std::ifstream file_input;
  int offset;
  std::string line;
  unsigned int cur_line = 0;
  bool prop_found = false;

  file_input.open(plist_loc.c_str());
  if(file_input.is_open()) {
    while(getline(file_input, line)) { // I changed this, see below
      cur_line++;

      if (prop_found == true) {
        std::string found_prop = line;
        found_prop = util::replace(found_prop, " ", "");
        found_prop = util::trim_from_beg(found_prop, "<string>");
        found_prop = util::trim_from_end(found_prop, "</string>");
        return found_prop;
      }

      if (util::has_text(line, plist_prop)) {
        prop_found = true;
      }
    }
    file_input.close();
  }
  return "prop_not_found";
}


void util::init_db()
{
  if (db_initialized == false) {
    db_initialized = true;
    char *error_msg = 0;
    int  ret_code;
    std::string sql_stmt;

    /* Open database */
    ret_code = sqlite3_open_v2("", &index_db, SQLITE_OPEN_READWRITE, NULL); /**< By leaving the first parameter sqlite creates a temporary database which has comparable speeds to a full fledged in-memory database */
    if( ret_code ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(index_db));
    }else{
      fprintf(stdout, "Opened database successfully\n");
    }

    sql_stmt = "CREATE TABLE `index` (" \
      "`ID`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE," \
      "`icon_location`	TEXT," \
      "`app_name`	TEXT," \
      "`app_location`	TEXT" \
      ");";

    /* Execute SQL statement */
    ret_code = sqlite3_exec(index_db, util::to_char(sql_stmt), generic_db_callback, 0, &error_msg);
    if( ret_code != SQLITE_OK ){
      if (util::has_text(error_msg, "already exists") == false) // omits the already exists error msg
        fprintf(stderr, "SQL error: %s\n", error_msg);
      sqlite3_free(error_msg);
    }else{
      fprintf(stdout, "Table created successfully\n");
    }
  }
}

void util::load_db()
{
  if (db_loaded == false) {
    int ret_code;
    sqlite3 *in_memory = index_db;
    sqlite3 *source_file;           /* Database connection opened on default_db_location.c_str() */
    sqlite3_backup *backup_obj;  /* Backup object used to copy data */
    sqlite3 *destination;             /* Database to copy to (source_file or in_memory) */
    sqlite3 *source;           /* Database to copy from (source_file or in_memory) */

    /* Open the database file identified by default_db_location.c_str(). Exit early if this fails
    ** for any reason. */
    ret_code = sqlite3_open(default_db_location.c_str(), &source_file);
    if( ret_code==SQLITE_OK ){

      source = source_file;
      destination   = in_memory;

      backup_obj = sqlite3_backup_init(destination, "main", source, "main");
      if( backup_obj ){
        (void)sqlite3_backup_step(backup_obj, -1);
        (void)sqlite3_backup_finish(backup_obj);
      }
      ret_code = sqlite3_errcode(destination);
    }

    /* Close the database connection opened on database file default_db_location.c_str()
    ** and return the result of this function. */
    (void)sqlite3_close(source_file);

    db_loaded = true;
  }
}


int util::generic_db_callback(void *data, int total_col_num, char **value, char **fields)
{
  for(int iter = 0; iter < total_col_num; iter++){
    printf("%s = %s\n", fields[iter], value[iter] ? value[iter] : "NULL");
  }
  printf("\n");
  return 0;
}

int util::flush_to_db(sqlite3 *in_memory, const char *file_name) {
  int ret_code;
  sqlite3 *destination_file;           // Database connection opened on file_name
  sqlite3_backup *backup_obj;  // Backup object used to copy data
  sqlite3 *destination;             // Database to copy to (destination_file or in_memory)
  sqlite3 *source;           // Database to copy from (destination_file or in_memory)

  ret_code = sqlite3_open(file_name, &destination_file);
  if( ret_code==SQLITE_OK ){

    source = in_memory;
    destination   = destination_file;

    backup_obj = sqlite3_backup_init(destination, "main", source, "main");
    if( backup_obj ){
      (void)sqlite3_backup_step(backup_obj, -1);
      (void)sqlite3_backup_finish(backup_obj);
    }
    ret_code = sqlite3_errcode(destination);
  }

  /* Close the database connection opened on database file file_name
  ** and return the result of this function. */
  db_opened = true;
  (void)sqlite3_close(destination_file);
  return ret_code;
}

std::string util::trim_from_beg(std::string text, std::string trim_param)
{
  std::string trimmed_text = text.substr(trim_param.size(), text.size());
  return trimmed_text;
}

std::string util::trim_from_end(std::string text, std::string trim_param)
{
  std::string trimmed_text = text.substr(0, text.size() - trim_param.size());
  return trimmed_text;
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

bool util::file_exists(std::string file_name)
{
  struct stat buf;
  if (stat(file_name.c_str(), &buf) != -1)
    {
      return true;
    }
  return false;
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
