# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = "D:\Apps\clion\Clion\CLion 2020.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Apps\clion\Clion\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\c++ exercise\Mall"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\c++ exercise\Mall\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Mall.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Mall.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Mall.dir/flags.make

CMakeFiles/Mall.dir/main.cpp.obj: CMakeFiles/Mall.dir/flags.make
CMakeFiles/Mall.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\c++ exercise\Mall\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Mall.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Mall.dir\main.cpp.obj -c "D:\c++ exercise\Mall\main.cpp"

CMakeFiles/Mall.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mall.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\c++ exercise\Mall\main.cpp" > CMakeFiles\Mall.dir\main.cpp.i

CMakeFiles/Mall.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mall.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\c++ exercise\Mall\main.cpp" -o CMakeFiles\Mall.dir\main.cpp.s

# Object files for target Mall
Mall_OBJECTS = \
"CMakeFiles/Mall.dir/main.cpp.obj"

# External object files for target Mall
Mall_EXTERNAL_OBJECTS =

Mall.exe: CMakeFiles/Mall.dir/main.cpp.obj
Mall.exe: CMakeFiles/Mall.dir/build.make
Mall.exe: CMakeFiles/Mall.dir/linklibs.rsp
Mall.exe: CMakeFiles/Mall.dir/objects1.rsp
Mall.exe: CMakeFiles/Mall.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\c++ exercise\Mall\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Mall.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Mall.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Mall.dir/build: Mall.exe

.PHONY : CMakeFiles/Mall.dir/build

CMakeFiles/Mall.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Mall.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Mall.dir/clean

CMakeFiles/Mall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\c++ exercise\Mall" "D:\c++ exercise\Mall" "D:\c++ exercise\Mall\cmake-build-debug" "D:\c++ exercise\Mall\cmake-build-debug" "D:\c++ exercise\Mall\cmake-build-debug\CMakeFiles\Mall.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Mall.dir/depend
