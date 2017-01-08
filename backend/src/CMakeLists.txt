find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)
#pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)


include_directories(
  ${GLIB2_INCLUDE_DIRS}
  ${SQLITE3_INCLUDE_DIRS}
  #${GTKMM3_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

link_directories(
   ${GLIB2_LIBRARY_DIRS}
#  ${GTKMM3_LIBRARY_DIRS}
  ${SQLITE3_LIBRARY_DIRS}
  )

add_definitions(
   ${GLIB2_CFLAGS_OTHER}
#  ${GTKMM3_CFLAGS_OTHER}
#  ${GTKMM_DEFINITIONS}
  )

add_subdirectory(Utilities)
#add_subdirectory(Audio)
#add_subdirectory(Utilities)
#add_subdirectory(Spectrum)
#add_subdirectory(Audio-Library)
#add_subdirectory(Audio-Info)

add_executable(jeff-backend
  main.cpp
#  GUI
#  Audio
#  Audio-Info
  Utilities
#  Audio-Library
#  Spectrum
  ) #more headers and cpp files can be added

target_compile_features(jeff-backend PRIVATE cxx_range_for)

target_link_libraries(jeff-backend
  ${GLIB2_LIBRARIES}
  ${SQLITE3_LIBRARIES}
  Utilities
  )

  #${GTKMM3_LIBRARIES}

#  GUI
#  Audio-Library
#  Audio
#  Audio-Info

#  Spectrum
#  -fopenmp
#  -lgobject-2.0
#  -lglib-2.0
#  )

 message(STATUS "Generarating ${CMAKE_SOURCE_DIR}/.clang_complete")
 get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
 file(WRITE ${CMAKE_SOURCE_DIR}/.clang_complete "")
 foreach(dir ${dirs})
   file(APPEND ${CMAKE_SOURCE_DIR}/.clang_complete "-I${dir}\n")
 endforeach()
 #string(REPLACE "'" "" CMAKE_CXX_FLAGS_SPLIT ${CMAKE_CXX_FLAGS})
 #string(REPLACE " " ";" CMAKE_CXX_FLAGS_SPLIT ${CMAKE_CXX_FLAGS_SPLIT})
 foreach(flag ${CMAKE_CXX_FLAGS_SPLIT})
   file(APPEND ${CMAKE_SOURCE_DIR}/.clang_complete "${flag}\n")
 endforeach()
