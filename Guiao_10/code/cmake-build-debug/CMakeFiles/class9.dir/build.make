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
CMAKE_COMMAND = /home/deadlock/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/231.8109.222/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/deadlock/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/231.8109.222/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/deadlock/Desktop/CG/Guiao_10/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/class9.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/class9.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/class9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class9.dir/flags.make

CMakeFiles/class9.dir/main.cpp.o: CMakeFiles/class9.dir/flags.make
CMakeFiles/class9.dir/main.cpp.o: /home/deadlock/Desktop/CG/Guiao_10/code/main.cpp
CMakeFiles/class9.dir/main.cpp.o: CMakeFiles/class9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class9.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/class9.dir/main.cpp.o -MF CMakeFiles/class9.dir/main.cpp.o.d -o CMakeFiles/class9.dir/main.cpp.o -c /home/deadlock/Desktop/CG/Guiao_10/code/main.cpp

CMakeFiles/class9.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class9.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/deadlock/Desktop/CG/Guiao_10/code/main.cpp > CMakeFiles/class9.dir/main.cpp.i

CMakeFiles/class9.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class9.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/deadlock/Desktop/CG/Guiao_10/code/main.cpp -o CMakeFiles/class9.dir/main.cpp.s

# Object files for target class9
class9_OBJECTS = \
"CMakeFiles/class9.dir/main.cpp.o"

# External object files for target class9
class9_EXTERNAL_OBJECTS =

class9: CMakeFiles/class9.dir/main.cpp.o
class9: CMakeFiles/class9.dir/build.make
class9: /usr/lib/x86_64-linux-gnu/libGL.so
class9: /usr/lib/x86_64-linux-gnu/libGLU.so
class9: /usr/lib/x86_64-linux-gnu/libglut.so
class9: /usr/lib/x86_64-linux-gnu/libGLEW.so
class9: /usr/lib/x86_64-linux-gnu/libIL.so
class9: CMakeFiles/class9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class9"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/class9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class9.dir/build: class9
.PHONY : CMakeFiles/class9.dir/build

CMakeFiles/class9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/class9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/class9.dir/clean

CMakeFiles/class9.dir/depend:
	cd /home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/deadlock/Desktop/CG/Guiao_10/code /home/deadlock/Desktop/CG/Guiao_10/code /home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug /home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug /home/deadlock/Desktop/CG/Guiao_10/code/cmake-build-debug/CMakeFiles/class9.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class9.dir/depend

