# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist

# Utility rule file for NightlyBuild.

# Include the progress variables for this target.
include test/CMakeFiles/NightlyBuild.dir/progress.make

test/CMakeFiles/NightlyBuild:
	cd /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/test && /opt/local/bin/ctest -D NightlyBuild

NightlyBuild: test/CMakeFiles/NightlyBuild
NightlyBuild: test/CMakeFiles/NightlyBuild.dir/build.make
.PHONY : NightlyBuild

# Rule to build all files generated by this target.
test/CMakeFiles/NightlyBuild.dir/build: NightlyBuild
.PHONY : test/CMakeFiles/NightlyBuild.dir/build

test/CMakeFiles/NightlyBuild.dir/clean:
	cd /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/test && $(CMAKE_COMMAND) -P CMakeFiles/NightlyBuild.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/NightlyBuild.dir/clean

test/CMakeFiles/NightlyBuild.dir/depend:
	cd /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6 /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/test /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/test /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/test/CMakeFiles/NightlyBuild.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/NightlyBuild.dir/depend
