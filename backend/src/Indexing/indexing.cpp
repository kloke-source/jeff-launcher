#include <Indexing/indexing.h>
#include <Utilities/util.h>
#include <vector>
#include <sqlite3.h>
#include <iostream>


std::vector<std::string> subdir_locations;
std::vector<std::string> file_locations;
sqlite3 *index_db;
int total_files=0;
int subdir_count=0;
std::string default_db_location;

bool db_loaded=false;
bool db_initialized=false;


void Indexing::init_db()
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

void Indexing::load_db()
{
  Indexing::initialize();
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

void Indexing::scan_dir(const char *dir_location){

  subdir_locations.push_back(dir_location);

  for (size_t subdir_iter = 0; subdir_iter < subdir_locations.size(); subdir_iter++){
    std::string file_location = subdir_locations[subdir_iter];
    if (file_location.substr(file_location.length() - 1) != "/")
      file_location += "/";

    GError *error = NULL;
    GError *subdir_error = NULL;

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
  //sqlite3 *index_db = index_db;
}

int AudioLibrary::generic_db_callback(void *data, int total_col_num, char **value, char **fields)
{
  for(int iter = 0; iter < total_col_num; iter++){
    printf("%s = %s\n", fields[iter], value[iter] ? value[iter] : "NULL");
  }
  printf("\n");
  return 0;
}

int Indexing::flush_to_db {
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
