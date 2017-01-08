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
  btree<std::string> mac_app_indexed_plists;
}

void DirIndex::search(std::string search_path, std::string directory)
{
  path = search_path;
  DirIndex::process_directory(directory);
}

void DirIndex::process_directory(std::string directory)
{
    std::string dir_to_open = path + directory;
    DIR* dir = opendir(dir_to_open.c_str());

    //set the new path for the content of the directory
    path = dir_to_open + "/";

    std::cout << "Process directory: " << dir_to_open.c_str() << std::endl;

    if(NULL == dir)
    {
        std::cout << "could not open directory: " << dir_to_open.c_str() << std::endl;
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

    std::cout << "Not a file or directory: " << entity->d_name << std::endl;
}

void DirIndex::process_file(std::string file)
{
  std::string file_loc = path + file;

      if (mac_app_indexed_plists.check(path) == false)
        {
      std::string plist_loc = path + "/Contents/Info.plist";

      if (util::file_exists(plist_loc)) {
        std::string exec_name = util::get_plist_property("CFBundleExecutable", plist_loc);
        std::string icon_name = util::get_plist_property("CFBundleIconFile", plist_loc);
        std::string raw_icon_name = util::trim_from_end(icon_name, ".icns");

        //std::cout << "Looking in Dir -> " << subdir_location << std::endl;
        //std::cout << "Icon name -> " << icon_name << std::endl;
        std::cout << "Dir -> " << path << std::endl;
        std::cout << "Icon name -> " << icon_name << std::endl;
        //std::string icns_file_loc = util::look_in_dir(subdir_location.c_str(), icon_name);

      }
      mac_app_indexed_plists.insert(path);
        }
}
#endif
