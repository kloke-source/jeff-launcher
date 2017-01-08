# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/WilliamSinclair/Documents/jeff-launcher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/WilliamSinclair/Documents/jeff-launcher/build

# Include any dependencies generated for this target.
include backend/src/Utilities/CMakeFiles/Utilities.dir/depend.make

# Include the progress variables for this target.
include backend/src/Utilities/CMakeFiles/Utilities.dir/progress.make

# Include the compile flags for this target's objects.
include backend/src/Utilities/CMakeFiles/Utilities.dir/flags.make

backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o: backend/src/Utilities/CMakeFiles/Utilities.dir/flags.make
backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o: ../backend/src/Utilities/util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/WilliamSinclair/Documents/jeff-launcher/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o"
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utilities.dir/util.cpp.o -c /Users/WilliamSinclair/Documents/jeff-launcher/backend/src/Utilities/util.cpp

backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utilities.dir/util.cpp.i"
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/WilliamSinclair/Documents/jeff-launcher/backend/src/Utilities/util.cpp > CMakeFiles/Utilities.dir/util.cpp.i

backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utilities.dir/util.cpp.s"
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/WilliamSinclair/Documents/jeff-launcher/backend/src/Utilities/util.cpp -o CMakeFiles/Utilities.dir/util.cpp.s

backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires:

.PHONY : backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires

backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides: backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires
	$(MAKE) -f backend/src/Utilities/CMakeFiles/Utilities.dir/build.make backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides.build
.PHONY : backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides

backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.provides.build: backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o


# Object files for target Utilities
Utilities_OBJECTS = \
"CMakeFiles/Utilities.dir/util.cpp.o"

# External object files for target Utilities
Utilities_EXTERNAL_OBJECTS =

backend/src/Utilities/libUtilities.a: backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o
backend/src/Utilities/libUtilities.a: backend/src/Utilities/CMakeFiles/Utilities.dir/build.make
backend/src/Utilities/libUtilities.a: backend/src/Utilities/CMakeFiles/Utilities.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/WilliamSinclair/Documents/jeff-launcher/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libUtilities.a"
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities && $(CMAKE_COMMAND) -P CMakeFiles/Utilities.dir/cmake_clean_target.cmake
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Utilities.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
backend/src/Utilities/CMakeFiles/Utilities.dir/build: backend/src/Utilities/libUtilities.a

.PHONY : backend/src/Utilities/CMakeFiles/Utilities.dir/build

backend/src/Utilities/CMakeFiles/Utilities.dir/requires: backend/src/Utilities/CMakeFiles/Utilities.dir/util.cpp.o.requires

.PHONY : backend/src/Utilities/CMakeFiles/Utilities.dir/requires

backend/src/Utilities/CMakeFiles/Utilities.dir/clean:
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities && $(CMAKE_COMMAND) -P CMakeFiles/Utilities.dir/cmake_clean.cmake
.PHONY : backend/src/Utilities/CMakeFiles/Utilities.dir/clean

backend/src/Utilities/CMakeFiles/Utilities.dir/depend:
	cd /Users/WilliamSinclair/Documents/jeff-launcher/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/WilliamSinclair/Documents/jeff-launcher /Users/WilliamSinclair/Documents/jeff-launcher/backend/src/Utilities /Users/WilliamSinclair/Documents/jeff-launcher/build /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities /Users/WilliamSinclair/Documents/jeff-launcher/build/backend/src/Utilities/CMakeFiles/Utilities.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : backend/src/Utilities/CMakeFiles/Utilities.dir/depend

