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
CMAKE_SOURCE_DIR = /Users/WilliamSinclair/Documents/dev/jeff-launcher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/WilliamSinclair/Documents/dev/jeff-launcher/build

# Include any dependencies generated for this target.
include backend/src/CMakeFiles/jeff-backend.dir/depend.make

# Include the progress variables for this target.
include backend/src/CMakeFiles/jeff-backend.dir/progress.make

# Include the compile flags for this target's objects.
include backend/src/CMakeFiles/jeff-backend.dir/flags.make

backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o: backend/src/CMakeFiles/jeff-backend.dir/flags.make
backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o: ../backend/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/WilliamSinclair/Documents/dev/jeff-launcher/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o"
	cd /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jeff-backend.dir/main.cpp.o -c /Users/WilliamSinclair/Documents/dev/jeff-launcher/backend/src/main.cpp

backend/src/CMakeFiles/jeff-backend.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jeff-backend.dir/main.cpp.i"
	cd /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/WilliamSinclair/Documents/dev/jeff-launcher/backend/src/main.cpp > CMakeFiles/jeff-backend.dir/main.cpp.i

backend/src/CMakeFiles/jeff-backend.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jeff-backend.dir/main.cpp.s"
	cd /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/WilliamSinclair/Documents/dev/jeff-launcher/backend/src/main.cpp -o CMakeFiles/jeff-backend.dir/main.cpp.s

backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.requires:

.PHONY : backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.requires

backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.provides: backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.requires
	$(MAKE) -f backend/src/CMakeFiles/jeff-backend.dir/build.make backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.provides.build
.PHONY : backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.provides

backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.provides.build: backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o


# Object files for target jeff-backend
jeff__backend_OBJECTS = \
"CMakeFiles/jeff-backend.dir/main.cpp.o"

# External object files for target jeff-backend
jeff__backend_EXTERNAL_OBJECTS =

../jeff-backend: backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o
../jeff-backend: backend/src/CMakeFiles/jeff-backend.dir/build.make
../jeff-backend: backend/src/Utilities/libUtilities.a
../jeff-backend: backend/src/CMakeFiles/jeff-backend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/WilliamSinclair/Documents/dev/jeff-launcher/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../jeff-backend"
	cd /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jeff-backend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
backend/src/CMakeFiles/jeff-backend.dir/build: ../jeff-backend

.PHONY : backend/src/CMakeFiles/jeff-backend.dir/build

backend/src/CMakeFiles/jeff-backend.dir/requires: backend/src/CMakeFiles/jeff-backend.dir/main.cpp.o.requires

.PHONY : backend/src/CMakeFiles/jeff-backend.dir/requires

backend/src/CMakeFiles/jeff-backend.dir/clean:
	cd /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src && $(CMAKE_COMMAND) -P CMakeFiles/jeff-backend.dir/cmake_clean.cmake
.PHONY : backend/src/CMakeFiles/jeff-backend.dir/clean

backend/src/CMakeFiles/jeff-backend.dir/depend:
	cd /Users/WilliamSinclair/Documents/dev/jeff-launcher/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/WilliamSinclair/Documents/dev/jeff-launcher /Users/WilliamSinclair/Documents/dev/jeff-launcher/backend/src /Users/WilliamSinclair/Documents/dev/jeff-launcher/build /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src /Users/WilliamSinclair/Documents/dev/jeff-launcher/build/backend/src/CMakeFiles/jeff-backend.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : backend/src/CMakeFiles/jeff-backend.dir/depend

