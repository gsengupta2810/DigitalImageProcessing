cmake_minimum_required(VERSION 2.8)
project( digital_image_processing )
find_package( OpenCV REQUIRED )
add_executable( blobs blobs.cpp )
target_link_libraries( blobs ${OpenCV_LIBS} )

add_executable( task task.cpp )
target_link_libraries( task ${OpenCV_LIBS} )

add_executable( task_1 task_1.cpp )
target_link_libraries( task_1 ${OpenCV_LIBS} )