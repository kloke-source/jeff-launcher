#ifndef DIR_INDEX_H
#define DIR_INDEX_H

#include <string>
#include <dirent.h>
#include <functional>

class DirIndex{
 public:
  static void search(std::string search_path, std::string directory);
 private:
  static void process_directory(std::string directory);
  static void process_file(std::string file);
  static void process_entity(struct dirent* entity);
};

namespace {
  std::string path = "/";
  std::vector<std::string> mac_app_sqlite_cache_fields;
  struct MacAppCache {
    std::string indexed_dir;
        std::vector<std::string> indexed_files;
    std::vector<std::string> indexed_file_locs;
};

std::vector<MacAppCache> indexed_mac_app_cache;
}

void DirIndex::search(std::string search_path, std::string directory)
{
  mac_app_sqlite_cache_fields.push_back("icon_location");
  mac_app_sqlite_cache_fields.push_back("app_name");
  mac_app_sqlite_cache_fields.push_back("app_location");

  path = search_path;
  DirIndex::process_directory(directory);

  for (size_t iter = 0; iter < indexed_mac_app_cache.size(); iter++) {
    std::string plist_loc = indexed_mac_app_cache[iter].indexed_dir + ".app/Contents/Info.plist";
    //std::cout << "Plist " << plist_loc << std::endl;
    /* code */

    if (util::file_exists(plist_loc)) {
      std::string exec_name = util::get_plist_property("CFBundleExecutable", plist_loc);
      std::string exec_loc = indexed_mac_app_cache[iter].indexed_dir + ".app/Contents/MacOS/" + util::trim_from_beg(exec_name, ">");
      std::string icon_name = util::get_plist_property("CFBundleIconFile", plist_loc);
      std::string display_name = util::get_plist_property("CFBundleDisplayName", plist_loc);
      std::string raw_icon_name = util::trim_from_end(icon_name, ".icns");

      std::vector<std::string> mac_app_sqlite_cache_values;
      mac_app_sqlite_cache_values.push_back("nothing");
      mac_app_sqlite_cache_values.push_back(util::trim_from_beg(exec_name, ">"));
      mac_app_sqlite_cache_values.push_back(exec_loc);

      if (util::file_exists(exec_loc))
      std::cout << exec_loc << std::endl;
      //if (util::file_exists(exec_loc))
      //std::cout << "Exec_loc " << exec_loc << std::endl;
      //std::cout << "Icns File Loc " << indexed_mac_app_cache[iter].indexed_files[util::search_vect(indexed_mac_app_cache[iter].indexed_files, icon_name).second] << std::endl;
/*
      for (size_t sub_iter = 0; sub_iter < indexed_mac_app_cache[iter].indexed_files.size(); sub_iter++) {
      //  std::cout << "Search text " << indexed_mac_app_cache[iter].indexed_files[sub_iter] << " Icon name " << icon_name << std::endl;
        if (util::has_text(indexed_mac_app_cache[iter].indexed_files[sub_iter], icon_name)) {
          std::cout << "Icns FileLoc " << indexed_mac_app_cache[iter].indexed_files[sub_iter] << std::endl;
          break;
        }

      }
      */
  }
  /*
  std::string file_loc = path + file;
  int found = path.find(".app");
  std::string app_root_fold = path.substr(0, found);

      if (mac_app_indexed_dirs.check(app_root_fold) == false)
        {
      std::string plist_loc = path + "Contents/Info.plist";
      std::cout << "Plist file " << plist_loc << std::endl;
      if (util::file_exists(plist_loc)) {
        std::string exec_name = util::get_plist_property("CFBundleExecutable", plist_loc);
        std::string icon_name = util::get_plist_property("CFBundleIconFile", plist_loc);
        std::string raw_icon_name = util::trim_from_end(icon_name, ".icns");

        //std::cout << "Looking in Dir -> " << subdir_location << std::endl;
        std::cout << "Icon name -> " << icon_name << std::endl;
        std::cout << "Dir -> " << path << std::endl;
        std::cout << "Icon name -> " << icon_name << std::endl;
        //std::string icns_file_loc = util::look_in_dir(subdir_location.c_str(), icon_name);

      }
      mac_app_indexed_dirs.insert(app_root_fold);
        }
        */
      }
    }


void DirIndex::process_directory(std::string directory)
{
    std::string dir_to_open = path + directory;
    DIR* dir = opendir(dir_to_open.c_str());

    //set the new path for the content of the directory
    path = dir_to_open + "/";

    //std::cout << "Process directory: " << dir_to_open.c_str() << std::endl;

    if(NULL == dir)
    {
      //  std::cout << "could not open directory: " << dir_to_open.c_str() << std::endl;
        return;
    }

    dirent* entity = readdir(dir);

    while(entity != NULL)
    {
        process_entity(entity);
        entity = readdir(dir);
    }

    //we finished with the directory so remove it from the path
    path.resize(path.length() - 1 - directory.length());
    closedir(dir);
}

void DirIndex::process_entity(struct dirent* entity)
{
    //find entity type
    if(entity->d_type == DT_DIR)
    {//it's an direcotry
        //don't process the  '..' and the '.' directories
        if(entity->d_name[0] == '.')
        {
            return;
        }

        //it's an directory so process it
        process_directory(std::string(entity->d_name));
        return;
    }

    if(entity->d_type == DT_REG)
    {//regular file
        process_file(std::string(entity->d_name));
        return;
    }

  //  std::cout << "Not a file or directory: " << entity->d_name << std::endl;
}

void DirIndex::process_file(std::string file)
{
  std::string file_loc = path + file;

  int found = path.find(".app");
  std::string app_root_fold = path.substr(0, found);

  //std::cout << "App root fold -> " << app_root_fold << std::endl;
  bool dir_already_indexed = false;
  for (size_t iter = 0; iter < indexed_mac_app_cache.size(); iter++) {
    if (indexed_mac_app_cache[iter].indexed_dir.compare(app_root_fold) == 0) {
      dir_already_indexed = true;
      indexed_mac_app_cache[iter].indexed_file_locs.push_back(file_loc);
      indexed_mac_app_cache[iter].indexed_files.push_back(file);
    }
  }

  if (dir_already_indexed == false)
  {
    MacAppCache mac_app_cache;
    mac_app_cache.indexed_dir = app_root_fold;
    mac_app_cache.indexed_file_locs.push_back(file_loc);
    indexed_mac_app_cache.push_back(mac_app_cache);
    indexed_mac_app_cache[indexed_mac_app_cache.size() - 1].indexed_file_locs.push_back(file_loc);
  }

}
#endif
