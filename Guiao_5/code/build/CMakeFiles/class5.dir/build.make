# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luisfernandes/Desktop/CG/Guiao_5/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luisfernandes/Desktop/CG/Guiao_5/code/build

# Include any dependencies generated for this target.
include CMakeFiles/class5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class5.dir/flags.make

CMakeFiles/class5.dir/main.cpp.o: CMakeFiles/class5.dir/flags.make
CMakeFiles/class5.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luisfernandes/Desktop/CG/Guiao_5/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class5.dir/main.cpp.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/class5.dir/main.cpp.o -c /home/luisfernandes/Desktop/CG/Guiao_5/code/main.cpp

CMakeFiles/class5.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class5.dir/main.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luisfernandes/Desktop/CG/Guiao_5/code/main.cpp > CMakeFiles/class5.dir/main.cpp.i

CMakeFiles/class5.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class5.dir/main.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luisfernandes/Desktop/CG/Guiao_5/code/main.cpp -o CMakeFiles/class5.dir/main.cpp.s

# Object files for target class5
class5_OBJECTS = \
"CMakeFiles/class5.dir/main.cpp.o"

# External object files for target class5
class5_EXTERNAL_OBJECTS =

class5: CMakeFiles/class5.dir/main.cpp.o
class5: CMakeFiles/class5.dir/build.make
class5: /usr/lib/x86_64-linux-gnu/libGL.so
class5: /usr/lib/x86_64-linux-gnu/libGLU.so
class5: /usr/lib/x86_64-linux-gnu/libglut.so
class5: /usr/lib/x86_64-linux-gnu/libXmu.so
class5: /usr/lib/x86_64-linux-gnu/libXi.so
class5: /usr/lib/x86_64-linux-gnu/libGLEW.so
class5: /usr/lib/x86_64-linux-gnu/libGL.so
class5: /usr/lib/x86_64-linux-gnu/libGLU.so
class5: /usr/lib/x86_64-linux-gnu/libglut.so
class5: /usr/lib/x86_64-linux-gnu/libXmu.so
class5: /usr/lib/x86_64-linux-gnu/libXi.so
class5: /usr/lib/x86_64-linux-gnu/libGLEW.so
class5: CMakeFiles/class5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luisfernandes/Desktop/CG/Guiao_5/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/class5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class5.dir/build: class5

.PHONY : CMakeFiles/class5.dir/build

CMakeFiles/class5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/class5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/class5.dir/clean

CMakeFiles/class5.dir/depend:
	cd /home/luisfernandes/Desktop/CG/Guiao_5/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luisfernandes/Desktop/CG/Guiao_5/code /home/luisfernandes/Desktop/CG/Guiao_5/code /home/luisfernandes/Desktop/CG/Guiao_5/code/build /home/luisfernandes/Desktop/CG/Guiao_5/code/build /home/luisfernandes/Desktop/CG/Guiao_5/code/build/CMakeFiles/class5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class5.dir/depend
