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
CMAKE_COMMAND = /home/just/CLion/clion-2019.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/just/CLion/clion-2019.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/just/semestr5/linux/linux_hools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/just/semestr5/linux/linux_hools/cmake-build-debug

# Include any dependencies generated for this target.
include serwer/CMakeFiles/serwer.dir/depend.make

# Include the progress variables for this target.
include serwer/CMakeFiles/serwer.dir/progress.make

# Include the compile flags for this target's objects.
include serwer/CMakeFiles/serwer.dir/flags.make

serwer/CMakeFiles/serwer.dir/serwer.c.o: serwer/CMakeFiles/serwer.dir/flags.make
serwer/CMakeFiles/serwer.dir/serwer.c.o: ../serwer/serwer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/just/semestr5/linux/linux_hools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object serwer/CMakeFiles/serwer.dir/serwer.c.o"
	cd /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serwer.dir/serwer.c.o   -c /home/just/semestr5/linux/linux_hools/serwer/serwer.c

serwer/CMakeFiles/serwer.dir/serwer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serwer.dir/serwer.c.i"
	cd /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/just/semestr5/linux/linux_hools/serwer/serwer.c > CMakeFiles/serwer.dir/serwer.c.i

serwer/CMakeFiles/serwer.dir/serwer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serwer.dir/serwer.c.s"
	cd /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/just/semestr5/linux/linux_hools/serwer/serwer.c -o CMakeFiles/serwer.dir/serwer.c.s

# Object files for target serwer
serwer_OBJECTS = \
"CMakeFiles/serwer.dir/serwer.c.o"

# External object files for target serwer
serwer_EXTERNAL_OBJECTS =

serwer/serwer: serwer/CMakeFiles/serwer.dir/serwer.c.o
serwer/serwer: serwer/CMakeFiles/serwer.dir/build.make
serwer/serwer: serwer/CMakeFiles/serwer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/just/semestr5/linux/linux_hools/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable serwer"
	cd /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serwer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serwer/CMakeFiles/serwer.dir/build: serwer/serwer

.PHONY : serwer/CMakeFiles/serwer.dir/build

serwer/CMakeFiles/serwer.dir/clean:
	cd /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer && $(CMAKE_COMMAND) -P CMakeFiles/serwer.dir/cmake_clean.cmake
.PHONY : serwer/CMakeFiles/serwer.dir/clean

serwer/CMakeFiles/serwer.dir/depend:
	cd /home/just/semestr5/linux/linux_hools/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/just/semestr5/linux/linux_hools /home/just/semestr5/linux/linux_hools/serwer /home/just/semestr5/linux/linux_hools/cmake-build-debug /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer /home/just/semestr5/linux/linux_hools/cmake-build-debug/serwer/CMakeFiles/serwer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serwer/CMakeFiles/serwer.dir/depend

