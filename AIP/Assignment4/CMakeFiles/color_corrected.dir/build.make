# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4

# Include any dependencies generated for this target.
include CMakeFiles/color_corrected.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/color_corrected.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/color_corrected.dir/flags.make

CMakeFiles/color_corrected.dir/color_correct.cpp.o: CMakeFiles/color_corrected.dir/flags.make
CMakeFiles/color_corrected.dir/color_correct.cpp.o: color_correct.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/color_corrected.dir/color_correct.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/color_corrected.dir/color_correct.cpp.o -c /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4/color_correct.cpp

CMakeFiles/color_corrected.dir/color_correct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color_corrected.dir/color_correct.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4/color_correct.cpp > CMakeFiles/color_corrected.dir/color_correct.cpp.i

CMakeFiles/color_corrected.dir/color_correct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color_corrected.dir/color_correct.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4/color_correct.cpp -o CMakeFiles/color_corrected.dir/color_correct.cpp.s

CMakeFiles/color_corrected.dir/color_correct.cpp.o.requires:
.PHONY : CMakeFiles/color_corrected.dir/color_correct.cpp.o.requires

CMakeFiles/color_corrected.dir/color_correct.cpp.o.provides: CMakeFiles/color_corrected.dir/color_correct.cpp.o.requires
	$(MAKE) -f CMakeFiles/color_corrected.dir/build.make CMakeFiles/color_corrected.dir/color_correct.cpp.o.provides.build
.PHONY : CMakeFiles/color_corrected.dir/color_correct.cpp.o.provides

CMakeFiles/color_corrected.dir/color_correct.cpp.o.provides.build: CMakeFiles/color_corrected.dir/color_correct.cpp.o

# Object files for target color_corrected
color_corrected_OBJECTS = \
"CMakeFiles/color_corrected.dir/color_correct.cpp.o"

# External object files for target color_corrected
color_corrected_EXTERNAL_OBJECTS =

color_corrected: CMakeFiles/color_corrected.dir/color_correct.cpp.o
color_corrected: CMakeFiles/color_corrected.dir/build.make
color_corrected: /usr/local/lib/libopencv_viz.so.2.4.9
color_corrected: /usr/local/lib/libopencv_videostab.so.2.4.9
color_corrected: /usr/local/lib/libopencv_ts.a
color_corrected: /usr/local/lib/libopencv_superres.so.2.4.9
color_corrected: /usr/local/lib/libopencv_stitching.so.2.4.9
color_corrected: /usr/local/lib/libopencv_contrib.so.2.4.9
color_corrected: /usr/lib/i386-linux-gnu/libGLU.so
color_corrected: /usr/lib/i386-linux-gnu/libGL.so
color_corrected: /usr/lib/i386-linux-gnu/libSM.so
color_corrected: /usr/lib/i386-linux-gnu/libICE.so
color_corrected: /usr/lib/i386-linux-gnu/libX11.so
color_corrected: /usr/lib/i386-linux-gnu/libXext.so
color_corrected: /usr/local/lib/libopencv_nonfree.so.2.4.9
color_corrected: /usr/local/lib/libopencv_ocl.so.2.4.9
color_corrected: /usr/local/lib/libopencv_gpu.so.2.4.9
color_corrected: /usr/local/lib/libopencv_photo.so.2.4.9
color_corrected: /usr/local/lib/libopencv_objdetect.so.2.4.9
color_corrected: /usr/local/lib/libopencv_legacy.so.2.4.9
color_corrected: /usr/local/lib/libopencv_video.so.2.4.9
color_corrected: /usr/local/lib/libopencv_ml.so.2.4.9
color_corrected: /usr/local/lib/libopencv_calib3d.so.2.4.9
color_corrected: /usr/local/lib/libopencv_features2d.so.2.4.9
color_corrected: /usr/local/lib/libopencv_highgui.so.2.4.9
color_corrected: /usr/local/lib/libopencv_imgproc.so.2.4.9
color_corrected: /usr/local/lib/libopencv_flann.so.2.4.9
color_corrected: /usr/local/lib/libopencv_core.so.2.4.9
color_corrected: CMakeFiles/color_corrected.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable color_corrected"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/color_corrected.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/color_corrected.dir/build: color_corrected
.PHONY : CMakeFiles/color_corrected.dir/build

CMakeFiles/color_corrected.dir/requires: CMakeFiles/color_corrected.dir/color_correct.cpp.o.requires
.PHONY : CMakeFiles/color_corrected.dir/requires

CMakeFiles/color_corrected.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/color_corrected.dir/cmake_clean.cmake
.PHONY : CMakeFiles/color_corrected.dir/clean

CMakeFiles/color_corrected.dir/depend:
	cd /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4 /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4 /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4 /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4 /home/gunjan/Desktop/practice/digital_image_processing/AIP/Assignment4/CMakeFiles/color_corrected.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/color_corrected.dir/depend

