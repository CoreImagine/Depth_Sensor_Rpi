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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/dept_upload/camport2_mod/sample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/dept_upload/camport2_mod/sample/build

# Include any dependencies generated for this target.
include CMakeFiles/SimpleView_FetchFrame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SimpleView_FetchFrame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SimpleView_FetchFrame.dir/flags.make

CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o: CMakeFiles/SimpleView_FetchFrame.dir/flags.make
CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o: ../SimpleView_FetchFrame/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/dept_upload/camport2_mod/sample/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o -c /home/pi/dept_upload/camport2_mod/sample/SimpleView_FetchFrame/main.cpp

CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/dept_upload/camport2_mod/sample/SimpleView_FetchFrame/main.cpp > CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.i

CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/dept_upload/camport2_mod/sample/SimpleView_FetchFrame/main.cpp -o CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.s

CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.requires:

.PHONY : CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.requires

CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.provides: CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SimpleView_FetchFrame.dir/build.make CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.provides.build
.PHONY : CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.provides

CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.provides.build: CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o


# Object files for target SimpleView_FetchFrame
SimpleView_FetchFrame_OBJECTS = \
"CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o"

# External object files for target SimpleView_FetchFrame
SimpleView_FetchFrame_EXTERNAL_OBJECTS =

bin/SimpleView_FetchFrame: CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o
bin/SimpleView_FetchFrame: CMakeFiles/SimpleView_FetchFrame.dir/build.make
bin/SimpleView_FetchFrame: libsample_common.a
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_videostab.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_ts.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_superres.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_stitching.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_ocl.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_gpu.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_contrib.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_photo.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_legacy.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_video.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_objdetect.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_ml.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_calib3d.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_features2d.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_flann.so.2.4.9
bin/SimpleView_FetchFrame: /usr/lib/arm-linux-gnueabihf/libopencv_core.so.2.4.9
bin/SimpleView_FetchFrame: CMakeFiles/SimpleView_FetchFrame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/dept_upload/camport2_mod/sample/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/SimpleView_FetchFrame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimpleView_FetchFrame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SimpleView_FetchFrame.dir/build: bin/SimpleView_FetchFrame

.PHONY : CMakeFiles/SimpleView_FetchFrame.dir/build

CMakeFiles/SimpleView_FetchFrame.dir/requires: CMakeFiles/SimpleView_FetchFrame.dir/SimpleView_FetchFrame/main.cpp.o.requires

.PHONY : CMakeFiles/SimpleView_FetchFrame.dir/requires

CMakeFiles/SimpleView_FetchFrame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimpleView_FetchFrame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimpleView_FetchFrame.dir/clean

CMakeFiles/SimpleView_FetchFrame.dir/depend:
	cd /home/pi/dept_upload/camport2_mod/sample/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/dept_upload/camport2_mod/sample /home/pi/dept_upload/camport2_mod/sample /home/pi/dept_upload/camport2_mod/sample/build /home/pi/dept_upload/camport2_mod/sample/build /home/pi/dept_upload/camport2_mod/sample/build/CMakeFiles/SimpleView_FetchFrame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SimpleView_FetchFrame.dir/depend

