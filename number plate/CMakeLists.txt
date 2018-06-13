cmake_minimum_required(VERSION 2.8)
project( A1 )
find_package( OpenCV REQUIRED )

add_executable( prep preprocess.cpp )
target_link_libraries( prep ${OpenCV_LIBS} )
