# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/98/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/98/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/theneonlightning/Algorithm_3Sem/Module4_Task1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Module4_Task1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Module4_Task1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Module4_Task1.dir/flags.make

CMakeFiles/Module4_Task1.dir/main.cpp.o: CMakeFiles/Module4_Task1.dir/flags.make
CMakeFiles/Module4_Task1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Module4_Task1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Module4_Task1.dir/main.cpp.o -c /home/theneonlightning/Algorithm_3Sem/Module4_Task1/main.cpp

CMakeFiles/Module4_Task1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Module4_Task1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theneonlightning/Algorithm_3Sem/Module4_Task1/main.cpp > CMakeFiles/Module4_Task1.dir/main.cpp.i

CMakeFiles/Module4_Task1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Module4_Task1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theneonlightning/Algorithm_3Sem/Module4_Task1/main.cpp -o CMakeFiles/Module4_Task1.dir/main.cpp.s

CMakeFiles/Module4_Task1.dir/biginteger.cpp.o: CMakeFiles/Module4_Task1.dir/flags.make
CMakeFiles/Module4_Task1.dir/biginteger.cpp.o: ../biginteger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Module4_Task1.dir/biginteger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Module4_Task1.dir/biginteger.cpp.o -c /home/theneonlightning/Algorithm_3Sem/Module4_Task1/biginteger.cpp

CMakeFiles/Module4_Task1.dir/biginteger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Module4_Task1.dir/biginteger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theneonlightning/Algorithm_3Sem/Module4_Task1/biginteger.cpp > CMakeFiles/Module4_Task1.dir/biginteger.cpp.i

CMakeFiles/Module4_Task1.dir/biginteger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Module4_Task1.dir/biginteger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theneonlightning/Algorithm_3Sem/Module4_Task1/biginteger.cpp -o CMakeFiles/Module4_Task1.dir/biginteger.cpp.s

# Object files for target Module4_Task1
Module4_Task1_OBJECTS = \
"CMakeFiles/Module4_Task1.dir/main.cpp.o" \
"CMakeFiles/Module4_Task1.dir/biginteger.cpp.o"

# External object files for target Module4_Task1
Module4_Task1_EXTERNAL_OBJECTS =

Module4_Task1: CMakeFiles/Module4_Task1.dir/main.cpp.o
Module4_Task1: CMakeFiles/Module4_Task1.dir/biginteger.cpp.o
Module4_Task1: CMakeFiles/Module4_Task1.dir/build.make
Module4_Task1: CMakeFiles/Module4_Task1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Module4_Task1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Module4_Task1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Module4_Task1.dir/build: Module4_Task1

.PHONY : CMakeFiles/Module4_Task1.dir/build

CMakeFiles/Module4_Task1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Module4_Task1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Module4_Task1.dir/clean

CMakeFiles/Module4_Task1.dir/depend:
	cd /home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/theneonlightning/Algorithm_3Sem/Module4_Task1 /home/theneonlightning/Algorithm_3Sem/Module4_Task1 /home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug /home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug /home/theneonlightning/Algorithm_3Sem/Module4_Task1/cmake-build-debug/CMakeFiles/Module4_Task1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Module4_Task1.dir/depend

