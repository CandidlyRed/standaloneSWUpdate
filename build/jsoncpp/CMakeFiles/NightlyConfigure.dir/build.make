# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/candidly/standaloneSWUpdate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/candidly/standaloneSWUpdate/build

# Utility rule file for NightlyConfigure.

# Include any custom commands dependencies for this target.
include jsoncpp/CMakeFiles/NightlyConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include jsoncpp/CMakeFiles/NightlyConfigure.dir/progress.make

jsoncpp/CMakeFiles/NightlyConfigure:
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp && /usr/bin/ctest -D NightlyConfigure

NightlyConfigure: jsoncpp/CMakeFiles/NightlyConfigure
NightlyConfigure: jsoncpp/CMakeFiles/NightlyConfigure.dir/build.make
.PHONY : NightlyConfigure

# Rule to build all files generated by this target.
jsoncpp/CMakeFiles/NightlyConfigure.dir/build: NightlyConfigure
.PHONY : jsoncpp/CMakeFiles/NightlyConfigure.dir/build

jsoncpp/CMakeFiles/NightlyConfigure.dir/clean:
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp && $(CMAKE_COMMAND) -P CMakeFiles/NightlyConfigure.dir/cmake_clean.cmake
.PHONY : jsoncpp/CMakeFiles/NightlyConfigure.dir/clean

jsoncpp/CMakeFiles/NightlyConfigure.dir/depend:
	cd /home/candidly/standaloneSWUpdate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/candidly/standaloneSWUpdate /home/candidly/standaloneSWUpdate/jsoncpp /home/candidly/standaloneSWUpdate/build /home/candidly/standaloneSWUpdate/build/jsoncpp /home/candidly/standaloneSWUpdate/build/jsoncpp/CMakeFiles/NightlyConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp/CMakeFiles/NightlyConfigure.dir/depend

