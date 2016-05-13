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
CMAKE_SOURCE_DIR = /home/gunjan/Desktop/practice/digital_image_processing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gunjan/Desktop/practice/digital_image_processing

# Include any dependencies generated for this target.
include CMakeFiles/affine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/affine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/affine.dir/flags.make

CMakeFiles/affine.dir/affine_transforms.cpp.o: CMakeFiles/affine.dir/flags.make
CMakeFiles/affine.dir/affine_transforms.cpp.o: affine_transforms.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gunjan/Desktop/practice/digital_image_processing/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/affine.dir/affine_transforms.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/affine.dir/affine_transforms.cpp.o -c /home/gunjan/Desktop/practice/digital_image_processing/affine_transforms.cpp

CMakeFiles/affine.dir/affine_transforms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/affine.dir/affine_transforms.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gunjan/Desktop/practice/digital_image_processing/affine_transforms.cpp > CMakeFiles/affine.dir/affine_transforms.cpp.i

CMakeFiles/affine.dir/affine_transforms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/affine.dir/affine_transforms.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gunjan/Desktop/practice/digital_image_processing/affine_transforms.cpp -o CMakeFiles/affine.dir/affine_transforms.cpp.s

CMakeFiles/affine.dir/affine_transforms.cpp.o.requires:
.PHONY : CMakeFiles/affine.dir/affine_transforms.cpp.o.requires

CMakeFiles/affine.dir/affine_transforms.cpp.o.provides: CMakeFiles/affine.dir/affine_transforms.cpp.o.requires
	$(MAKE) -f CMakeFiles/affine.dir/build.make CMakeFiles/affine.dir/affine_transforms.cpp.o.provides.build
.PHONY : CMakeFiles/affine.dir/affine_transforms.cpp.o.provides

CMakeFiles/affine.dir/affine_transforms.cpp.o.provides.build: CMakeFiles/affine.dir/affine_transforms.cpp.o

# Object files for target affine
affine_OBJECTS = \
"CMakeFiles/affine.dir/affine_transforms.cpp.o"

# External object files for target affine
affine_EXTERNAL_OBJECTS =

affine: CMakeFiles/affine.dir/affine_transforms.cpp.o
affine: CMakeFiles/affine.dir/build.make
affine: /usr/local/lib/libopencv_viz.so.2.4.9
affine: /usr/local/lib/libopencv_videostab.so.2.4.9
affine: /usr/local/lib/libopencv_ts.a
affine: /usr/local/lib/libopencv_superres.so.2.4.9
affine: /usr/local/lib/libopencv_stitching.so.2.4.9
affine: /usr/local/lib/libopencv_contrib.so.2.4.9
affine: /usr/lib/i386-linux-gnu/libGLU.so
affine: /usr/lib/i386-linux-gnu/libGL.so
affine: /usr/lib/i386-linux-gnu/libSM.so
affine: /usr/lib/i386-linux-gnu/libICE.so
affine: /usr/lib/i386-linux-gnu/libX11.so
affine: /usr/lib/i386-linux-gnu/libXext.so
affine: /usr/local/lib/libopencv_nonfree.so.2.4.9
affine: /usr/local/lib/libopencv_ocl.so.2.4.9
affine: /usr/local/lib/libopencv_gpu.so.2.4.9
affine: /usr/local/lib/libopencv_photo.so.2.4.9
affine: /usr/local/lib/libopencv_objdetect.so.2.4.9
affine: /usr/local/lib/libopencv_legacy.so.2.4.9
affine: /usr/local/lib/libopencv_video.so.2.4.9
affine: /usr/local/lib/libopencv_ml.so.2.4.9
affine: /usr/local/lib/libopencv_calib3d.so.2.4.9
affine: /usr/local/lib/libopencv_features2d.so.2.4.9
affine: /usr/local/lib/libopencv_highgui.so.2.4.9
affine: /usr/local/lib/libopencv_imgproc.so.2.4.9
affine: /usr/local/lib/libopencv_flann.so.2.4.9
affine: /usr/local/lib/libopencv_core.so.2.4.9
affine: CMakeFiles/affine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable affine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/affine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/affine.dir/build: affine
.PHONY : CMakeFiles/affine.dir/build

CMakeFiles/affine.dir/requires: CMakeFiles/affine.dir/affine_transforms.cpp.o.requires
.PHONY : CMakeFiles/affine.dir/requires

CMakeFiles/affine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/affine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/affine.dir/clean

CMakeFiles/affine.dir/depend:
	cd /home/gunjan/Desktop/practice/digital_image_processing && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gunjan/Desktop/practice/digital_image_processing /home/gunjan/Desktop/practice/digital_image_processing /home/gunjan/Desktop/practice/digital_image_processing /home/gunjan/Desktop/practice/digital_image_processing /home/gunjan/Desktop/practice/digital_image_processing/CMakeFiles/affine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/affine.dir/depend
