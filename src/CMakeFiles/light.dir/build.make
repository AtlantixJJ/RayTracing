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
include src/CMakeFiles/light.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/light.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/light.dir/flags.make

src/CMakeFiles/light.dir/light/light.cpp.o: src/CMakeFiles/light.dir/flags.make
src/CMakeFiles/light.dir/light/light.cpp.o: src/light/light.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/light.dir/light/light.cpp.o"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/light.dir/light/light.cpp.o -c /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/light.cpp

src/CMakeFiles/light.dir/light/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/light.dir/light/light.cpp.i"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/light.cpp > CMakeFiles/light.dir/light/light.cpp.i

src/CMakeFiles/light.dir/light/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/light.dir/light/light.cpp.s"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/light.cpp -o CMakeFiles/light.dir/light/light.cpp.s

src/CMakeFiles/light.dir/light/light.cpp.o.requires:

.PHONY : src/CMakeFiles/light.dir/light/light.cpp.o.requires

src/CMakeFiles/light.dir/light/light.cpp.o.provides: src/CMakeFiles/light.dir/light/light.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/light.dir/build.make src/CMakeFiles/light.dir/light/light.cpp.o.provides.build
.PHONY : src/CMakeFiles/light.dir/light/light.cpp.o.provides

src/CMakeFiles/light.dir/light/light.cpp.o.provides.build: src/CMakeFiles/light.dir/light/light.cpp.o


src/CMakeFiles/light.dir/light/pointlight.cpp.o: src/CMakeFiles/light.dir/flags.make
src/CMakeFiles/light.dir/light/pointlight.cpp.o: src/light/pointlight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/light.dir/light/pointlight.cpp.o"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/light.dir/light/pointlight.cpp.o -c /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/pointlight.cpp

src/CMakeFiles/light.dir/light/pointlight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/light.dir/light/pointlight.cpp.i"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/pointlight.cpp > CMakeFiles/light.dir/light/pointlight.cpp.i

src/CMakeFiles/light.dir/light/pointlight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/light.dir/light/pointlight.cpp.s"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/pointlight.cpp -o CMakeFiles/light.dir/light/pointlight.cpp.s

src/CMakeFiles/light.dir/light/pointlight.cpp.o.requires:

.PHONY : src/CMakeFiles/light.dir/light/pointlight.cpp.o.requires

src/CMakeFiles/light.dir/light/pointlight.cpp.o.provides: src/CMakeFiles/light.dir/light/pointlight.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/light.dir/build.make src/CMakeFiles/light.dir/light/pointlight.cpp.o.provides.build
.PHONY : src/CMakeFiles/light.dir/light/pointlight.cpp.o.provides

src/CMakeFiles/light.dir/light/pointlight.cpp.o.provides.build: src/CMakeFiles/light.dir/light/pointlight.cpp.o


src/CMakeFiles/light.dir/light/rectlight.cpp.o: src/CMakeFiles/light.dir/flags.make
src/CMakeFiles/light.dir/light/rectlight.cpp.o: src/light/rectlight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/light.dir/light/rectlight.cpp.o"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/light.dir/light/rectlight.cpp.o -c /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/rectlight.cpp

src/CMakeFiles/light.dir/light/rectlight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/light.dir/light/rectlight.cpp.i"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/rectlight.cpp > CMakeFiles/light.dir/light/rectlight.cpp.i

src/CMakeFiles/light.dir/light/rectlight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/light.dir/light/rectlight.cpp.s"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/light/rectlight.cpp -o CMakeFiles/light.dir/light/rectlight.cpp.s

src/CMakeFiles/light.dir/light/rectlight.cpp.o.requires:

.PHONY : src/CMakeFiles/light.dir/light/rectlight.cpp.o.requires

src/CMakeFiles/light.dir/light/rectlight.cpp.o.provides: src/CMakeFiles/light.dir/light/rectlight.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/light.dir/build.make src/CMakeFiles/light.dir/light/rectlight.cpp.o.provides.build
.PHONY : src/CMakeFiles/light.dir/light/rectlight.cpp.o.provides

src/CMakeFiles/light.dir/light/rectlight.cpp.o.provides.build: src/CMakeFiles/light.dir/light/rectlight.cpp.o


# Object files for target light
light_OBJECTS = \
"CMakeFiles/light.dir/light/light.cpp.o" \
"CMakeFiles/light.dir/light/pointlight.cpp.o" \
"CMakeFiles/light.dir/light/rectlight.cpp.o"

# External object files for target light
light_EXTERNAL_OBJECTS =

src/lib/liblight.a: src/CMakeFiles/light.dir/light/light.cpp.o
src/lib/liblight.a: src/CMakeFiles/light.dir/light/pointlight.cpp.o
src/lib/liblight.a: src/CMakeFiles/light.dir/light/rectlight.cpp.o
src/lib/liblight.a: src/CMakeFiles/light.dir/build.make
src/lib/liblight.a: src/CMakeFiles/light.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xujianjin/Desktop/C++/RayTracing/RayTracing/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library lib/liblight.a"
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && $(CMAKE_COMMAND) -P CMakeFiles/light.dir/cmake_clean_target.cmake
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/light.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/light.dir/build: src/lib/liblight.a

.PHONY : src/CMakeFiles/light.dir/build

src/CMakeFiles/light.dir/requires: src/CMakeFiles/light.dir/light/light.cpp.o.requires
src/CMakeFiles/light.dir/requires: src/CMakeFiles/light.dir/light/pointlight.cpp.o.requires
src/CMakeFiles/light.dir/requires: src/CMakeFiles/light.dir/light/rectlight.cpp.o.requires

.PHONY : src/CMakeFiles/light.dir/requires

src/CMakeFiles/light.dir/clean:
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src && $(CMAKE_COMMAND) -P CMakeFiles/light.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/light.dir/clean

src/CMakeFiles/light.dir/depend:
	cd /Users/xujianjin/Desktop/C++/RayTracing/RayTracing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xujianjin/Desktop/C++/RayTracing/RayTracing /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src /Users/xujianjin/Desktop/C++/RayTracing/RayTracing /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src /Users/xujianjin/Desktop/C++/RayTracing/RayTracing/src/CMakeFiles/light.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/light.dir/depend
