project(jeff-backend)
cmake_minimum_required(VERSION 2.6)
add_subdirectory(backend)

set_target_properties(jeff-backend PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_DEBUG_POSTFIX "_debug" CACHE STRING "Set Debug library postfix" FORCE) #changes the debug postfix to _debug
set_target_properties(jeff-backend PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}) #sets the debug postfix
