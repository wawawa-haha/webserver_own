# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/code/sm_own

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/code/sm_own/build

# Include any dependencies generated for this target.
include CMakeFiles/x.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/x.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/x.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/x.dir/flags.make

CMakeFiles/x.dir/log.cpp.o: CMakeFiles/x.dir/flags.make
CMakeFiles/x.dir/log.cpp.o: ../log.cpp
CMakeFiles/x.dir/log.cpp.o: CMakeFiles/x.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/sm_own/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/x.dir/log.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/x.dir/log.cpp.o -MF CMakeFiles/x.dir/log.cpp.o.d -o CMakeFiles/x.dir/log.cpp.o -c /root/code/sm_own/log.cpp

CMakeFiles/x.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/x.dir/log.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/sm_own/log.cpp > CMakeFiles/x.dir/log.cpp.i

CMakeFiles/x.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/x.dir/log.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/sm_own/log.cpp -o CMakeFiles/x.dir/log.cpp.s

CMakeFiles/x.dir/test.cpp.o: CMakeFiles/x.dir/flags.make
CMakeFiles/x.dir/test.cpp.o: ../test.cpp
CMakeFiles/x.dir/test.cpp.o: CMakeFiles/x.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/sm_own/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/x.dir/test.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/x.dir/test.cpp.o -MF CMakeFiles/x.dir/test.cpp.o.d -o CMakeFiles/x.dir/test.cpp.o -c /root/code/sm_own/test.cpp

CMakeFiles/x.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/x.dir/test.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/sm_own/test.cpp > CMakeFiles/x.dir/test.cpp.i

CMakeFiles/x.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/x.dir/test.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/sm_own/test.cpp -o CMakeFiles/x.dir/test.cpp.s

CMakeFiles/x.dir/loggers.cpp.o: CMakeFiles/x.dir/flags.make
CMakeFiles/x.dir/loggers.cpp.o: ../loggers.cpp
CMakeFiles/x.dir/loggers.cpp.o: CMakeFiles/x.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/sm_own/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/x.dir/loggers.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/x.dir/loggers.cpp.o -MF CMakeFiles/x.dir/loggers.cpp.o.d -o CMakeFiles/x.dir/loggers.cpp.o -c /root/code/sm_own/loggers.cpp

CMakeFiles/x.dir/loggers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/x.dir/loggers.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/sm_own/loggers.cpp > CMakeFiles/x.dir/loggers.cpp.i

CMakeFiles/x.dir/loggers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/x.dir/loggers.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/sm_own/loggers.cpp -o CMakeFiles/x.dir/loggers.cpp.s

CMakeFiles/x.dir/util.cpp.o: CMakeFiles/x.dir/flags.make
CMakeFiles/x.dir/util.cpp.o: ../util.cpp
CMakeFiles/x.dir/util.cpp.o: CMakeFiles/x.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/sm_own/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/x.dir/util.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/x.dir/util.cpp.o -MF CMakeFiles/x.dir/util.cpp.o.d -o CMakeFiles/x.dir/util.cpp.o -c /root/code/sm_own/util.cpp

CMakeFiles/x.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/x.dir/util.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/sm_own/util.cpp > CMakeFiles/x.dir/util.cpp.i

CMakeFiles/x.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/x.dir/util.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/sm_own/util.cpp -o CMakeFiles/x.dir/util.cpp.s

CMakeFiles/x.dir/config.cpp.o: CMakeFiles/x.dir/flags.make
CMakeFiles/x.dir/config.cpp.o: ../config.cpp
CMakeFiles/x.dir/config.cpp.o: CMakeFiles/x.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/sm_own/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/x.dir/config.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/x.dir/config.cpp.o -MF CMakeFiles/x.dir/config.cpp.o.d -o CMakeFiles/x.dir/config.cpp.o -c /root/code/sm_own/config.cpp

CMakeFiles/x.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/x.dir/config.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/sm_own/config.cpp > CMakeFiles/x.dir/config.cpp.i

CMakeFiles/x.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/x.dir/config.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/sm_own/config.cpp -o CMakeFiles/x.dir/config.cpp.s

# Object files for target x
x_OBJECTS = \
"CMakeFiles/x.dir/log.cpp.o" \
"CMakeFiles/x.dir/test.cpp.o" \
"CMakeFiles/x.dir/loggers.cpp.o" \
"CMakeFiles/x.dir/util.cpp.o" \
"CMakeFiles/x.dir/config.cpp.o"

# External object files for target x
x_EXTERNAL_OBJECTS =

../bin/x: CMakeFiles/x.dir/log.cpp.o
../bin/x: CMakeFiles/x.dir/test.cpp.o
../bin/x: CMakeFiles/x.dir/loggers.cpp.o
../bin/x: CMakeFiles/x.dir/util.cpp.o
../bin/x: CMakeFiles/x.dir/config.cpp.o
../bin/x: CMakeFiles/x.dir/build.make
../bin/x: CMakeFiles/x.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/code/sm_own/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../bin/x"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/x.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/x.dir/build: ../bin/x
.PHONY : CMakeFiles/x.dir/build

CMakeFiles/x.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/x.dir/cmake_clean.cmake
.PHONY : CMakeFiles/x.dir/clean

CMakeFiles/x.dir/depend:
	cd /root/code/sm_own/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/code/sm_own /root/code/sm_own /root/code/sm_own/build /root/code/sm_own/build /root/code/sm_own/build/CMakeFiles/x.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/x.dir/depend

