# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ffmpeglearning.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ffmpeglearning.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ffmpeglearning.dir/flags.make

CMakeFiles/ffmpeglearning.dir/main.cpp.obj: CMakeFiles/ffmpeglearning.dir/flags.make
CMakeFiles/ffmpeglearning.dir/main.cpp.obj: CMakeFiles/ffmpeglearning.dir/includes_CXX.rsp
CMakeFiles/ffmpeglearning.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ffmpeglearning.dir/main.cpp.obj"
	C:\Users\st199\Documents\Environment\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ffmpeglearning.dir\main.cpp.obj -c C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\main.cpp

CMakeFiles/ffmpeglearning.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ffmpeglearning.dir/main.cpp.i"
	C:\Users\st199\Documents\Environment\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\main.cpp > CMakeFiles\ffmpeglearning.dir\main.cpp.i

CMakeFiles/ffmpeglearning.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ffmpeglearning.dir/main.cpp.s"
	C:\Users\st199\Documents\Environment\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\main.cpp -o CMakeFiles\ffmpeglearning.dir\main.cpp.s

# Object files for target ffmpeglearning
ffmpeglearning_OBJECTS = \
"CMakeFiles/ffmpeglearning.dir/main.cpp.obj"

# External object files for target ffmpeglearning
ffmpeglearning_EXTERNAL_OBJECTS =

ffmpeglearning.exe: CMakeFiles/ffmpeglearning.dir/main.cpp.obj
ffmpeglearning.exe: CMakeFiles/ffmpeglearning.dir/build.make
ffmpeglearning.exe: CMakeFiles/ffmpeglearning.dir/linklibs.rsp
ffmpeglearning.exe: CMakeFiles/ffmpeglearning.dir/objects1.rsp
ffmpeglearning.exe: CMakeFiles/ffmpeglearning.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ffmpeglearning.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ffmpeglearning.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ffmpeglearning.dir/build: ffmpeglearning.exe
.PHONY : CMakeFiles/ffmpeglearning.dir/build

CMakeFiles/ffmpeglearning.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ffmpeglearning.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ffmpeglearning.dir/clean

CMakeFiles/ffmpeglearning.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\cmake-build-debug C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\cmake-build-debug C:\Users\st199\Documents\projects\C++Projects\ffmpeglearning\cmake-build-debug\CMakeFiles\ffmpeglearning.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ffmpeglearning.dir/depend

