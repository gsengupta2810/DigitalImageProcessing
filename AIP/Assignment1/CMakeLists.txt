cmake_minimum_required(VERSION 2.8)
project( A1 )
find_package( OpenCV REQUIRED )

add_executable( one one.cpp )
target_link_libraries( one ${OpenCV_LIBS} )

add_executable( two two.cpp )
target_link_libraries( two ${OpenCV_LIBS} )

add_executable( three haris.cpp )
target_link_libraries( three ${OpenCV_LIBS} )

add_executable( four harris.cpp )
target_link_libraries( four ${OpenCV_LIBS} )
