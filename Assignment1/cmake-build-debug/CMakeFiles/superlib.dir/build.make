# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/superlib.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/superlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/superlib.dir/flags.make

CMakeFiles/superlib.dir/src/main.cpp.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/superlib.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/src/main.cpp.o -c /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/main.cpp

CMakeFiles/superlib.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/main.cpp > CMakeFiles/superlib.dir/src/main.cpp.i

CMakeFiles/superlib.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/main.cpp -o CMakeFiles/superlib.dir/src/main.cpp.s

CMakeFiles/superlib.dir/src/Customer.cpp.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/src/Customer.cpp.o: ../src/Customer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/superlib.dir/src/Customer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/src/Customer.cpp.o -c /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Customer.cpp

CMakeFiles/superlib.dir/src/Customer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/src/Customer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Customer.cpp > CMakeFiles/superlib.dir/src/Customer.cpp.i

CMakeFiles/superlib.dir/src/Customer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/src/Customer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Customer.cpp -o CMakeFiles/superlib.dir/src/Customer.cpp.s

CMakeFiles/superlib.dir/src/Studio.cpp.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/src/Studio.cpp.o: ../src/Studio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/superlib.dir/src/Studio.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/src/Studio.cpp.o -c /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Studio.cpp

CMakeFiles/superlib.dir/src/Studio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/src/Studio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Studio.cpp > CMakeFiles/superlib.dir/src/Studio.cpp.i

CMakeFiles/superlib.dir/src/Studio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/src/Studio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Studio.cpp -o CMakeFiles/superlib.dir/src/Studio.cpp.s

CMakeFiles/superlib.dir/src/Trainer.cpp.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/src/Trainer.cpp.o: ../src/Trainer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/superlib.dir/src/Trainer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/src/Trainer.cpp.o -c /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Trainer.cpp

CMakeFiles/superlib.dir/src/Trainer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/src/Trainer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Trainer.cpp > CMakeFiles/superlib.dir/src/Trainer.cpp.i

CMakeFiles/superlib.dir/src/Trainer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/src/Trainer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Trainer.cpp -o CMakeFiles/superlib.dir/src/Trainer.cpp.s

CMakeFiles/superlib.dir/src/Workout.cpp.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/src/Workout.cpp.o: ../src/Workout.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/superlib.dir/src/Workout.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/src/Workout.cpp.o -c /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Workout.cpp

CMakeFiles/superlib.dir/src/Workout.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/src/Workout.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Workout.cpp > CMakeFiles/superlib.dir/src/Workout.cpp.i

CMakeFiles/superlib.dir/src/Workout.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/src/Workout.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Workout.cpp -o CMakeFiles/superlib.dir/src/Workout.cpp.s

CMakeFiles/superlib.dir/src/Action.cpp.o: CMakeFiles/superlib.dir/flags.make
CMakeFiles/superlib.dir/src/Action.cpp.o: ../src/Action.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/superlib.dir/src/Action.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/superlib.dir/src/Action.cpp.o -c /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Action.cpp

CMakeFiles/superlib.dir/src/Action.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/superlib.dir/src/Action.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Action.cpp > CMakeFiles/superlib.dir/src/Action.cpp.i

CMakeFiles/superlib.dir/src/Action.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/superlib.dir/src/Action.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/src/Action.cpp -o CMakeFiles/superlib.dir/src/Action.cpp.s

# Object files for target superlib
superlib_OBJECTS = \
"CMakeFiles/superlib.dir/src/main.cpp.o" \
"CMakeFiles/superlib.dir/src/Customer.cpp.o" \
"CMakeFiles/superlib.dir/src/Studio.cpp.o" \
"CMakeFiles/superlib.dir/src/Trainer.cpp.o" \
"CMakeFiles/superlib.dir/src/Workout.cpp.o" \
"CMakeFiles/superlib.dir/src/Action.cpp.o"

# External object files for target superlib
superlib_EXTERNAL_OBJECTS =

superlib: CMakeFiles/superlib.dir/src/main.cpp.o
superlib: CMakeFiles/superlib.dir/src/Customer.cpp.o
superlib: CMakeFiles/superlib.dir/src/Studio.cpp.o
superlib: CMakeFiles/superlib.dir/src/Trainer.cpp.o
superlib: CMakeFiles/superlib.dir/src/Workout.cpp.o
superlib: CMakeFiles/superlib.dir/src/Action.cpp.o
superlib: CMakeFiles/superlib.dir/build.make
superlib: CMakeFiles/superlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable superlib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/superlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/superlib.dir/build: superlib
.PHONY : CMakeFiles/superlib.dir/build

CMakeFiles/superlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/superlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/superlib.dir/clean

CMakeFiles/superlib.dir/depend:
	cd /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1 /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1 /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug /mnt/c/Users/Omri/CLionProjects/SPL/Assignment1/cmake-build-debug/CMakeFiles/superlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/superlib.dir/depend

