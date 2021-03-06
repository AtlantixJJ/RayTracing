# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xujianjin/Desktop/C++/RayTracing/RayTracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xujianjin/Desktop/C++/RayTracing/RayTracing

# Include any dependencies generated for this target.
include tools/CMakeFiles/raytracing.dir/depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/raytracing.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/raytracing.dir/flags.make

tools/CMakeFiles/raytracing.dir/main.cpp.o: tools/CMakeFiles/raytracing.dir/flags.make
tools/CMakeFiles/raytracing.dir/main.cpp.o: tools/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/raytracing.dir/main.cpp.o"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && /Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytracing.dir/main.cpp.o -c /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/main.cpp

tools/CMakeFiles/raytracing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytracing.dir/main.cpp.i"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/main.cpp > CMakeFiles/raytracing.dir/main.cpp.i

tools/CMakeFiles/raytracing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytracing.dir/main.cpp.s"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/main.cpp -o CMakeFiles/raytracing.dir/main.cpp.s

tools/CMakeFiles/raytracing.dir/main.cpp.o.requires:

.PHONY : tools/CMakeFiles/raytracing.dir/main.cpp.o.requires

tools/CMakeFiles/raytracing.dir/main.cpp.o.provides: tools/CMakeFiles/raytracing.dir/main.cpp.o.requires
	$(MAKE) -f tools/CMakeFiles/raytracing.dir/build.make tools/CMakeFiles/raytracing.dir/main.cpp.o.provides.build
.PHONY : tools/CMakeFiles/raytracing.dir/main.cpp.o.provides

tools/CMakeFiles/raytracing.dir/main.cpp.o.provides.build: tools/CMakeFiles/raytracing.dir/main.cpp.o


# Object files for target raytracing
raytracing_OBJECTS = \
"CMakeFiles/raytracing.dir/main.cpp.o"

# External object files for target raytracing
raytracing_EXTERNAL_OBJECTS =

tools/bin/raytracing: tools/CMakeFiles/raytracing.dir/main.cpp.o
tools/bin/raytracing: tools/CMakeFiles/raytracing.dir/build.make
tools/bin/raytracing: src/lib/libengine.a
tools/bin/raytracing: src/lib/libscene.a
tools/bin/raytracing: externals/jsoncpp/src/lib_json/libjsoncpp.a
tools/bin/raytracing: src/lib/libobject.a
tools/bin/raytracing: src/lib/libutil.a
tools/bin/raytracing: src/lib/liblight.a
tools/bin/raytracing: src/lib/libcommon.a
tools/bin/raytracing: tools/CMakeFiles/raytracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/raytracing"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/raytracing.dir/build: tools/bin/raytracing

.PHONY : tools/CMakeFiles/raytracing.dir/build

tools/CMakeFiles/raytracing.dir/requires: tools/CMakeFiles/raytracing.dir/main.cpp.o.requires

.PHONY : tools/CMakeFiles/raytracing.dir/requires

tools/CMakeFiles/raytracing.dir/clean:
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && $(CMAKE_COMMAND) -P CMakeFiles/raytracing.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/raytracing.dir/clean

tools/CMakeFiles/raytracing.dir/depend:
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xujianjin/Desktop/C++/RayTracing/RayTracing /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools /Users/xujianjin/Desktop/C++/RayTracing/RayTracing /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/CMakeFiles/raytracing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/raytracing.dir/depend

