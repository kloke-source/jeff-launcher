#ifndef INITIALIZE_HH
#define INITIALIZE_HH

#include <glib.h>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <cstdio>

class Indexing;
class Indexing {
 public:
  static void initialize();
  static void init_db();
  static void load_db();
  static void scan_dir(const char *dir_location);
  static int generic_db_callback(void *data, int total_col_num, char **value, char **fields);
  static int flush_to_db(sqlite3 *pInMemory, const char *file_name);
#endif
