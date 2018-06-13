cmake_minimum_required(VERSION 2.8)
project( A1 )
find_package( OpenCV REQUIRED )

add_executable( out cie_learn.cpp )
target_link_libraries( out ${OpenCV_LIBS} )

add_executable( color_corrected color_correct.cpp )
target_link_libraries( color_corrected ${OpenCV_LIBS} )

add_executable( part1 part1.cpp )
target_link_libraries( part1 ${OpenCV_LIBS} )

add_executable( part3 part3.cpp )
target_link_libraries( part3 ${OpenCV_LIBS} )
