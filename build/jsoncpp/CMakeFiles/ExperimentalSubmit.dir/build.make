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

# Utility rule file for ExperimentalSubmit.

# Include any custom commands dependencies for this target.
include jsoncpp/CMakeFiles/ExperimentalSubmit.dir/compiler_depend.make

# Include the progress variables for this target.
include jsoncpp/CMakeFiles/ExperimentalSubmit.dir/progress.make

jsoncpp/CMakeFiles/ExperimentalSubmit:
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp && /usr/bin/ctest -D ExperimentalSubmit

ExperimentalSubmit: jsoncpp/CMakeFiles/ExperimentalSubmit
ExperimentalSubmit: jsoncpp/CMakeFiles/ExperimentalSubmit.dir/build.make
.PHONY : ExperimentalSubmit

# Rule to build all files generated by this target.
jsoncpp/CMakeFiles/ExperimentalSubmit.dir/build: ExperimentalSubmit
.PHONY : jsoncpp/CMakeFiles/ExperimentalSubmit.dir/build

jsoncpp/CMakeFiles/ExperimentalSubmit.dir/clean:
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalSubmit.dir/cmake_clean.cmake
.PHONY : jsoncpp/CMakeFiles/ExperimentalSubmit.dir/clean

jsoncpp/CMakeFiles/ExperimentalSubmit.dir/depend:
	cd /home/candidly/standaloneSWUpdate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/candidly/standaloneSWUpdate /home/candidly/standaloneSWUpdate/jsoncpp /home/candidly/standaloneSWUpdate/build /home/candidly/standaloneSWUpdate/build/jsoncpp /home/candidly/standaloneSWUpdate/build/jsoncpp/CMakeFiles/ExperimentalSubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp/CMakeFiles/ExperimentalSubmit.dir/depend

