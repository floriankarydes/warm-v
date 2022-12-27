cmake_minimum_required( VERSION 3.10 )
project( WArM-V VERSION 1.0 )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories( include )

add_executable( helloworld src/helloworld.cpp )
target_link_libraries( helloworld ${OpenCV_LIBS} )

add_executable( stitching src/stitching.cpp )
target_link_libraries( stitching ${OpenCV_LIBS} )

add_executable( stitching_detailed src/stitching_detailed.cpp )
target_link_libraries( stitching_detailed ${OpenCV_LIBS} )
