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
CMAKE_COMMAND = /home/peter/Desktop/clion-2017.3.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/peter/Desktop/clion-2017.3.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/peter/CLionProjects/LeanNNs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peter/CLionProjects/LeanNNs/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LeanNNs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LeanNNs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LeanNNs.dir/flags.make

CMakeFiles/LeanNNs.dir/main.cpp.o: CMakeFiles/LeanNNs.dir/flags.make
CMakeFiles/LeanNNs.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/CLionProjects/LeanNNs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LeanNNs.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LeanNNs.dir/main.cpp.o -c /home/peter/CLionProjects/LeanNNs/main.cpp

CMakeFiles/LeanNNs.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LeanNNs.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/peter/CLionProjects/LeanNNs/main.cpp > CMakeFiles/LeanNNs.dir/main.cpp.i

CMakeFiles/LeanNNs.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LeanNNs.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/peter/CLionProjects/LeanNNs/main.cpp -o CMakeFiles/LeanNNs.dir/main.cpp.s

CMakeFiles/LeanNNs.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/LeanNNs.dir/main.cpp.o.requires

CMakeFiles/LeanNNs.dir/main.cpp.o.provides: CMakeFiles/LeanNNs.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/LeanNNs.dir/build.make CMakeFiles/LeanNNs.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/LeanNNs.dir/main.cpp.o.provides

CMakeFiles/LeanNNs.dir/main.cpp.o.provides.build: CMakeFiles/LeanNNs.dir/main.cpp.o


CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o: CMakeFiles/LeanNNs.dir/flags.make
CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o: ../NeuralNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/CLionProjects/LeanNNs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o -c /home/peter/CLionProjects/LeanNNs/NeuralNetwork.cpp

CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/peter/CLionProjects/LeanNNs/NeuralNetwork.cpp > CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.i

CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/peter/CLionProjects/LeanNNs/NeuralNetwork.cpp -o CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.s

CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.requires:

.PHONY : CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.requires

CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.provides: CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.requires
	$(MAKE) -f CMakeFiles/LeanNNs.dir/build.make CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.provides.build
.PHONY : CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.provides

CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.provides.build: CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o


CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o: CMakeFiles/LeanNNs.dir/flags.make
CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o: ../GeneticAlgorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/CLionProjects/LeanNNs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o -c /home/peter/CLionProjects/LeanNNs/GeneticAlgorithm.cpp

CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/peter/CLionProjects/LeanNNs/GeneticAlgorithm.cpp > CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.i

CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/peter/CLionProjects/LeanNNs/GeneticAlgorithm.cpp -o CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.s

CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.requires:

.PHONY : CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.requires

CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.provides: CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.requires
	$(MAKE) -f CMakeFiles/LeanNNs.dir/build.make CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.provides.build
.PHONY : CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.provides

CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.provides.build: CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o


CMakeFiles/LeanNNs.dir/AIAgent.cpp.o: CMakeFiles/LeanNNs.dir/flags.make
CMakeFiles/LeanNNs.dir/AIAgent.cpp.o: ../AIAgent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/CLionProjects/LeanNNs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LeanNNs.dir/AIAgent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LeanNNs.dir/AIAgent.cpp.o -c /home/peter/CLionProjects/LeanNNs/AIAgent.cpp

CMakeFiles/LeanNNs.dir/AIAgent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LeanNNs.dir/AIAgent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/peter/CLionProjects/LeanNNs/AIAgent.cpp > CMakeFiles/LeanNNs.dir/AIAgent.cpp.i

CMakeFiles/LeanNNs.dir/AIAgent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LeanNNs.dir/AIAgent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/peter/CLionProjects/LeanNNs/AIAgent.cpp -o CMakeFiles/LeanNNs.dir/AIAgent.cpp.s

CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.requires:

.PHONY : CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.requires

CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.provides: CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.requires
	$(MAKE) -f CMakeFiles/LeanNNs.dir/build.make CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.provides.build
.PHONY : CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.provides

CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.provides.build: CMakeFiles/LeanNNs.dir/AIAgent.cpp.o


# Object files for target LeanNNs
LeanNNs_OBJECTS = \
"CMakeFiles/LeanNNs.dir/main.cpp.o" \
"CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o" \
"CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o" \
"CMakeFiles/LeanNNs.dir/AIAgent.cpp.o"

# External object files for target LeanNNs
LeanNNs_EXTERNAL_OBJECTS =

LeanNNs: CMakeFiles/LeanNNs.dir/main.cpp.o
LeanNNs: CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o
LeanNNs: CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o
LeanNNs: CMakeFiles/LeanNNs.dir/AIAgent.cpp.o
LeanNNs: CMakeFiles/LeanNNs.dir/build.make
LeanNNs: CMakeFiles/LeanNNs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/peter/CLionProjects/LeanNNs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable LeanNNs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LeanNNs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LeanNNs.dir/build: LeanNNs

.PHONY : CMakeFiles/LeanNNs.dir/build

CMakeFiles/LeanNNs.dir/requires: CMakeFiles/LeanNNs.dir/main.cpp.o.requires
CMakeFiles/LeanNNs.dir/requires: CMakeFiles/LeanNNs.dir/NeuralNetwork.cpp.o.requires
CMakeFiles/LeanNNs.dir/requires: CMakeFiles/LeanNNs.dir/GeneticAlgorithm.cpp.o.requires
CMakeFiles/LeanNNs.dir/requires: CMakeFiles/LeanNNs.dir/AIAgent.cpp.o.requires

.PHONY : CMakeFiles/LeanNNs.dir/requires

CMakeFiles/LeanNNs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LeanNNs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LeanNNs.dir/clean

CMakeFiles/LeanNNs.dir/depend:
	cd /home/peter/CLionProjects/LeanNNs/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peter/CLionProjects/LeanNNs /home/peter/CLionProjects/LeanNNs /home/peter/CLionProjects/LeanNNs/cmake-build-debug /home/peter/CLionProjects/LeanNNs/cmake-build-debug /home/peter/CLionProjects/LeanNNs/cmake-build-debug/CMakeFiles/LeanNNs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LeanNNs.dir/depend

