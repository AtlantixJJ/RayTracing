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
include tools/CMakeFiles/model.dir/depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/model.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/model.dir/flags.make

tools/CMakeFiles/model.dir/modeling.cpp.o: tools/CMakeFiles/model.dir/flags.make
tools/CMakeFiles/model.dir/modeling.cpp.o: tools/modeling.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/model.dir/modeling.cpp.o"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && /Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model.dir/modeling.cpp.o -c /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/modeling.cpp

tools/CMakeFiles/model.dir/modeling.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model.dir/modeling.cpp.i"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/modeling.cpp > CMakeFiles/model.dir/modeling.cpp.i

tools/CMakeFiles/model.dir/modeling.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model.dir/modeling.cpp.s"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/modeling.cpp -o CMakeFiles/model.dir/modeling.cpp.s

tools/CMakeFiles/model.dir/modeling.cpp.o.requires:

.PHONY : tools/CMakeFiles/model.dir/modeling.cpp.o.requires

tools/CMakeFiles/model.dir/modeling.cpp.o.provides: tools/CMakeFiles/model.dir/modeling.cpp.o.requires
	$(MAKE) -f tools/CMakeFiles/model.dir/build.make tools/CMakeFiles/model.dir/modeling.cpp.o.provides.build
.PHONY : tools/CMakeFiles/model.dir/modeling.cpp.o.provides

tools/CMakeFiles/model.dir/modeling.cpp.o.provides.build: tools/CMakeFiles/model.dir/modeling.cpp.o


# Object files for target model
model_OBJECTS = \
"CMakeFiles/model.dir/modeling.cpp.o"

# External object files for target model
model_EXTERNAL_OBJECTS =

tools/bin/model: tools/CMakeFiles/model.dir/modeling.cpp.o
tools/bin/model: tools/CMakeFiles/model.dir/build.make
tools/bin/model: src/lib/libobject.a
tools/bin/model: externals/jsoncpp/src/lib_json/libjsoncpp.a
tools/bin/model: src/lib/libutil.a
tools/bin/model: src/lib/libcommon.a
tools/bin/model: tools/CMakeFiles/model.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/model"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/model.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/model.dir/build: tools/bin/model

.PHONY : tools/CMakeFiles/model.dir/build

tools/CMakeFiles/model.dir/requires: tools/CMakeFiles/model.dir/modeling.cpp.o.requires

.PHONY : tools/CMakeFiles/model.dir/requires

tools/CMakeFiles/model.dir/clean:
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools && $(CMAKE_COMMAND) -P CMakeFiles/model.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/model.dir/clean

tools/CMakeFiles/model.dir/depend:
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xujianjin/Desktop/C++/RayTracing/RayTracing /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools /Users/xujianjin/Desktop/C++/RayTracing/RayTracing /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/tools/CMakeFiles/model.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/model.dir/depend

