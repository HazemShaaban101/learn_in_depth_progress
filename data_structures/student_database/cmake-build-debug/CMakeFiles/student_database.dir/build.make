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
CMAKE_SOURCE_DIR = /mnt/c/Users/Hazem/Desktop/student_database

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/student_database.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/student_database.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/student_database.dir/flags.make

CMakeFiles/student_database.dir/main.c.o: CMakeFiles/student_database.dir/flags.make
CMakeFiles/student_database.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/student_database.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/student_database.dir/main.c.o   -c /mnt/c/Users/Hazem/Desktop/student_database/main.c

CMakeFiles/student_database.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/student_database.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Hazem/Desktop/student_database/main.c > CMakeFiles/student_database.dir/main.c.i

CMakeFiles/student_database.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/student_database.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Hazem/Desktop/student_database/main.c -o CMakeFiles/student_database.dir/main.c.s

CMakeFiles/student_database.dir/database.c.o: CMakeFiles/student_database.dir/flags.make
CMakeFiles/student_database.dir/database.c.o: ../database.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/student_database.dir/database.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/student_database.dir/database.c.o   -c /mnt/c/Users/Hazem/Desktop/student_database/database.c

CMakeFiles/student_database.dir/database.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/student_database.dir/database.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Hazem/Desktop/student_database/database.c > CMakeFiles/student_database.dir/database.c.i

CMakeFiles/student_database.dir/database.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/student_database.dir/database.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Hazem/Desktop/student_database/database.c -o CMakeFiles/student_database.dir/database.c.s

# Object files for target student_database
student_database_OBJECTS = \
"CMakeFiles/student_database.dir/main.c.o" \
"CMakeFiles/student_database.dir/database.c.o"

# External object files for target student_database
student_database_EXTERNAL_OBJECTS =

student_database: CMakeFiles/student_database.dir/main.c.o
student_database: CMakeFiles/student_database.dir/database.c.o
student_database: CMakeFiles/student_database.dir/build.make
student_database: CMakeFiles/student_database.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable student_database"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/student_database.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/student_database.dir/build: student_database

.PHONY : CMakeFiles/student_database.dir/build

CMakeFiles/student_database.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/student_database.dir/cmake_clean.cmake
.PHONY : CMakeFiles/student_database.dir/clean

CMakeFiles/student_database.dir/depend:
	cd /mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Hazem/Desktop/student_database /mnt/c/Users/Hazem/Desktop/student_database /mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug /mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug /mnt/c/Users/Hazem/Desktop/student_database/cmake-build-debug/CMakeFiles/student_database.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/student_database.dir/depend

