# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = "/Users/shaileibovich/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/173.4674.29/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/shaileibovich/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/173.4674.29/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shaileibovich/CLionProjects/FinalProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FinalProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FinalProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FinalProject.dir/flags.make

CMakeFiles/FinalProject.dir/main.c.o: CMakeFiles/FinalProject.dir/flags.make
CMakeFiles/FinalProject.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/FinalProject.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FinalProject.dir/main.c.o   -c /Users/shaileibovich/CLionProjects/FinalProject/main.c

CMakeFiles/FinalProject.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FinalProject.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/shaileibovich/CLionProjects/FinalProject/main.c > CMakeFiles/FinalProject.dir/main.c.i

CMakeFiles/FinalProject.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FinalProject.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/shaileibovich/CLionProjects/FinalProject/main.c -o CMakeFiles/FinalProject.dir/main.c.s

CMakeFiles/FinalProject.dir/main.c.o.requires:

.PHONY : CMakeFiles/FinalProject.dir/main.c.o.requires

CMakeFiles/FinalProject.dir/main.c.o.provides: CMakeFiles/FinalProject.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/FinalProject.dir/build.make CMakeFiles/FinalProject.dir/main.c.o.provides.build
.PHONY : CMakeFiles/FinalProject.dir/main.c.o.provides

CMakeFiles/FinalProject.dir/main.c.o.provides.build: CMakeFiles/FinalProject.dir/main.c.o


CMakeFiles/FinalProject.dir/GameBoard.c.o: CMakeFiles/FinalProject.dir/flags.make
CMakeFiles/FinalProject.dir/GameBoard.c.o: ../GameBoard.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/FinalProject.dir/GameBoard.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FinalProject.dir/GameBoard.c.o   -c /Users/shaileibovich/CLionProjects/FinalProject/GameBoard.c

CMakeFiles/FinalProject.dir/GameBoard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FinalProject.dir/GameBoard.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/shaileibovich/CLionProjects/FinalProject/GameBoard.c > CMakeFiles/FinalProject.dir/GameBoard.c.i

CMakeFiles/FinalProject.dir/GameBoard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FinalProject.dir/GameBoard.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/shaileibovich/CLionProjects/FinalProject/GameBoard.c -o CMakeFiles/FinalProject.dir/GameBoard.c.s

CMakeFiles/FinalProject.dir/GameBoard.c.o.requires:

.PHONY : CMakeFiles/FinalProject.dir/GameBoard.c.o.requires

CMakeFiles/FinalProject.dir/GameBoard.c.o.provides: CMakeFiles/FinalProject.dir/GameBoard.c.o.requires
	$(MAKE) -f CMakeFiles/FinalProject.dir/build.make CMakeFiles/FinalProject.dir/GameBoard.c.o.provides.build
.PHONY : CMakeFiles/FinalProject.dir/GameBoard.c.o.provides

CMakeFiles/FinalProject.dir/GameBoard.c.o.provides.build: CMakeFiles/FinalProject.dir/GameBoard.c.o


CMakeFiles/FinalProject.dir/utils.c.o: CMakeFiles/FinalProject.dir/flags.make
CMakeFiles/FinalProject.dir/utils.c.o: ../utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/FinalProject.dir/utils.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FinalProject.dir/utils.c.o   -c /Users/shaileibovich/CLionProjects/FinalProject/utils.c

CMakeFiles/FinalProject.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FinalProject.dir/utils.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/shaileibovich/CLionProjects/FinalProject/utils.c > CMakeFiles/FinalProject.dir/utils.c.i

CMakeFiles/FinalProject.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FinalProject.dir/utils.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/shaileibovich/CLionProjects/FinalProject/utils.c -o CMakeFiles/FinalProject.dir/utils.c.s

CMakeFiles/FinalProject.dir/utils.c.o.requires:

.PHONY : CMakeFiles/FinalProject.dir/utils.c.o.requires

CMakeFiles/FinalProject.dir/utils.c.o.provides: CMakeFiles/FinalProject.dir/utils.c.o.requires
	$(MAKE) -f CMakeFiles/FinalProject.dir/build.make CMakeFiles/FinalProject.dir/utils.c.o.provides.build
.PHONY : CMakeFiles/FinalProject.dir/utils.c.o.provides

CMakeFiles/FinalProject.dir/utils.c.o.provides.build: CMakeFiles/FinalProject.dir/utils.c.o


CMakeFiles/FinalProject.dir/GameManager.c.o: CMakeFiles/FinalProject.dir/flags.make
CMakeFiles/FinalProject.dir/GameManager.c.o: ../GameManager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/FinalProject.dir/GameManager.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FinalProject.dir/GameManager.c.o   -c /Users/shaileibovich/CLionProjects/FinalProject/GameManager.c

CMakeFiles/FinalProject.dir/GameManager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FinalProject.dir/GameManager.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/shaileibovich/CLionProjects/FinalProject/GameManager.c > CMakeFiles/FinalProject.dir/GameManager.c.i

CMakeFiles/FinalProject.dir/GameManager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FinalProject.dir/GameManager.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/shaileibovich/CLionProjects/FinalProject/GameManager.c -o CMakeFiles/FinalProject.dir/GameManager.c.s

CMakeFiles/FinalProject.dir/GameManager.c.o.requires:

.PHONY : CMakeFiles/FinalProject.dir/GameManager.c.o.requires

CMakeFiles/FinalProject.dir/GameManager.c.o.provides: CMakeFiles/FinalProject.dir/GameManager.c.o.requires
	$(MAKE) -f CMakeFiles/FinalProject.dir/build.make CMakeFiles/FinalProject.dir/GameManager.c.o.provides.build
.PHONY : CMakeFiles/FinalProject.dir/GameManager.c.o.provides

CMakeFiles/FinalProject.dir/GameManager.c.o.provides.build: CMakeFiles/FinalProject.dir/GameManager.c.o


# Object files for target FinalProject
FinalProject_OBJECTS = \
"CMakeFiles/FinalProject.dir/main.c.o" \
"CMakeFiles/FinalProject.dir/GameBoard.c.o" \
"CMakeFiles/FinalProject.dir/utils.c.o" \
"CMakeFiles/FinalProject.dir/GameManager.c.o"

# External object files for target FinalProject
FinalProject_EXTERNAL_OBJECTS =

FinalProject: CMakeFiles/FinalProject.dir/main.c.o
FinalProject: CMakeFiles/FinalProject.dir/GameBoard.c.o
FinalProject: CMakeFiles/FinalProject.dir/utils.c.o
FinalProject: CMakeFiles/FinalProject.dir/GameManager.c.o
FinalProject: CMakeFiles/FinalProject.dir/build.make
FinalProject: CMakeFiles/FinalProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable FinalProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FinalProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FinalProject.dir/build: FinalProject

.PHONY : CMakeFiles/FinalProject.dir/build

CMakeFiles/FinalProject.dir/requires: CMakeFiles/FinalProject.dir/main.c.o.requires
CMakeFiles/FinalProject.dir/requires: CMakeFiles/FinalProject.dir/GameBoard.c.o.requires
CMakeFiles/FinalProject.dir/requires: CMakeFiles/FinalProject.dir/utils.c.o.requires
CMakeFiles/FinalProject.dir/requires: CMakeFiles/FinalProject.dir/GameManager.c.o.requires

.PHONY : CMakeFiles/FinalProject.dir/requires

CMakeFiles/FinalProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FinalProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FinalProject.dir/clean

CMakeFiles/FinalProject.dir/depend:
	cd /Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shaileibovich/CLionProjects/FinalProject /Users/shaileibovich/CLionProjects/FinalProject /Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug /Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug /Users/shaileibovich/CLionProjects/FinalProject/cmake-build-debug/CMakeFiles/FinalProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FinalProject.dir/depend

