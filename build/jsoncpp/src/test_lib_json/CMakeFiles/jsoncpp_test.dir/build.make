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
include jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.make

# Include the progress variables for this target.
include jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/progress.make

# Include the compile flags for this target's objects.
include jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o: /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/jsontest.cpp
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o -MF CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o.d -o CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o -c /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/jsontest.cpp

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_test.dir/jsontest.cpp.i"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/jsontest.cpp > CMakeFiles/jsoncpp_test.dir/jsontest.cpp.i

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_test.dir/jsontest.cpp.s"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/jsontest.cpp -o CMakeFiles/jsoncpp_test.dir/jsontest.cpp.s

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o: /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/fuzz.cpp
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o -MF CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o.d -o CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o -c /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/fuzz.cpp

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_test.dir/fuzz.cpp.i"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/fuzz.cpp > CMakeFiles/jsoncpp_test.dir/fuzz.cpp.i

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_test.dir/fuzz.cpp.s"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/fuzz.cpp -o CMakeFiles/jsoncpp_test.dir/fuzz.cpp.s

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.o: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/flags.make
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.o: /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/main.cpp
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.o: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.o"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.o -MF CMakeFiles/jsoncpp_test.dir/main.cpp.o.d -o CMakeFiles/jsoncpp_test.dir/main.cpp.o -c /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/main.cpp

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_test.dir/main.cpp.i"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/main.cpp > CMakeFiles/jsoncpp_test.dir/main.cpp.i

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_test.dir/main.cpp.s"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json/main.cpp -o CMakeFiles/jsoncpp_test.dir/main.cpp.s

# Object files for target jsoncpp_test
jsoncpp_test_OBJECTS = \
"CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o" \
"CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o" \
"CMakeFiles/jsoncpp_test.dir/main.cpp.o"

# External object files for target jsoncpp_test
jsoncpp_test_EXTERNAL_OBJECTS =

jsoncpp/src/test_lib_json/jsoncpp_test: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/jsontest.cpp.o
jsoncpp/src/test_lib_json/jsoncpp_test: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/fuzz.cpp.o
jsoncpp/src/test_lib_json/jsoncpp_test: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/main.cpp.o
jsoncpp/src/test_lib_json/jsoncpp_test: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build.make
jsoncpp/src/test_lib_json/jsoncpp_test: jsoncpp/src/lib_json/libjsoncpp.so.1.9.5
jsoncpp/src/test_lib_json/jsoncpp_test: jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/candidly/standaloneSWUpdate/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable jsoncpp_test"
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && ./jsoncpp_test

# Rule to build all files generated by this target.
jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build: jsoncpp/src/test_lib_json/jsoncpp_test
.PHONY : jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/clean:
	cd /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_test.dir/cmake_clean.cmake
.PHONY : jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/clean

jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/depend:
	cd /home/candidly/standaloneSWUpdate/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/candidly/standaloneSWUpdate /home/candidly/standaloneSWUpdate/jsoncpp/src/test_lib_json /home/candidly/standaloneSWUpdate/build /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json /home/candidly/standaloneSWUpdate/build/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/depend

