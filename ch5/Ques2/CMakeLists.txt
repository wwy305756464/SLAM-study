cmake_minimum_required( VERSION 2.8 )
project(Prob2)
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-O3" )

add_executable(Prob2 Prob2.cpp)

# 链接OpenCV库
## target_link_libraries(Prob2 ${OpenCV_LIBS})
include_directories( /usr/local/Cellar/opencv@2/2.4.13.7_11/include)
