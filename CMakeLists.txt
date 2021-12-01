cmake_minimum_required(VERSION 3.20)
project(ffmpeglearning)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(ffmpeglib/include)
link_directories(ffmpeglib/lib)

link_libraries(
#        ffmpeglearning
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)
add_executable(ffmpeglearning main.cpp)