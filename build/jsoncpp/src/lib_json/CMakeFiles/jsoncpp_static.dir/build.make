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

# Include any dependencies generated for this target.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/compiler_depend.make

# Include the progress variables for this target.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/progress.make

# Include the compile flags for this target's objects.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/flags.make

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/flags.make
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o: /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_reader.cpp
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o -MF CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o.d -o CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o -c /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_reader.cpp

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_static.dir/json_reader.cpp.i"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_reader.cpp > CMakeFiles/jsoncpp_static.dir/json_reader.cpp.i

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_static.dir/json_reader.cpp.s"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_reader.cpp -o CMakeFiles/jsoncpp_static.dir/json_reader.cpp.s

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/flags.make
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.o: /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_value.cpp
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.o"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.o -MF CMakeFiles/jsoncpp_static.dir/json_value.cpp.o.d -o CMakeFiles/jsoncpp_static.dir/json_value.cpp.o -c /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_value.cpp

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_static.dir/json_value.cpp.i"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_value.cpp > CMakeFiles/jsoncpp_static.dir/json_value.cpp.i

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_static.dir/json_value.cpp.s"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_value.cpp -o CMakeFiles/jsoncpp_static.dir/json_value.cpp.s

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/flags.make
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o: /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_writer.cpp
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o -MF CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o.d -o CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o -c /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_writer.cpp

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_static.dir/json_writer.cpp.i"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_writer.cpp > CMakeFiles/jsoncpp_static.dir/json_writer.cpp.i

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_static.dir/json_writer.cpp.s"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json/json_writer.cpp -o CMakeFiles/jsoncpp_static.dir/json_writer.cpp.s

# Object files for target jsoncpp_static
jsoncpp_static_OBJECTS = \
"CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o" \
"CMakeFiles/jsoncpp_static.dir/json_value.cpp.o" \
"CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o"

# External object files for target jsoncpp_static
jsoncpp_static_EXTERNAL_OBJECTS =

jsoncpp/src/lib_json/libjsoncpp.a: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_reader.cpp.o
jsoncpp/src/lib_json/libjsoncpp.a: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_value.cpp.o
jsoncpp/src/lib_json/libjsoncpp.a: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/json_writer.cpp.o
jsoncpp/src/lib_json/libjsoncpp.a: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/build.make
jsoncpp/src/lib_json/libjsoncpp.a: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libjsoncpp.a"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_static.dir/cmake_clean_target.cmake
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/build: jsoncpp/src/lib_json/libjsoncpp.a
.PHONY : jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/build

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/clean:
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_static.dir/cmake_clean.cmake
.PHONY : jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/clean

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/depend:
	cd /home/candidly/standaloneSWUpdate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/candidly/standaloneSWUpdate /home/candidly/standaloneSWUpdate/jsoncpp/src/lib_json /home/candidly/standaloneSWUpdate/build /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json /home/candidly/standaloneSWUpdate/build/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp/src/lib_json/CMakeFiles/jsoncpp_static.dir/depend

