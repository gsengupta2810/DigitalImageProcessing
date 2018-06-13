cmake_minimum_required(VERSION 2.8)
project( A1 )
find_package( OpenCV REQUIRED )

add_executable( out depth_map.cpp )
target_link_libraries( out ${OpenCV_LIBS} )
