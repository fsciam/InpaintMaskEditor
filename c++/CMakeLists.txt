cmake_minimum_required(VERSION 2.8)
project( PhotoRestoration )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( PhotoRestoration main.cpp LiveSketcher.cpp)
target_link_libraries( PhotoRestoration ${OpenCV_LIBS})
