cmake_minimum_required(VERSION 3.8)
project(Deque)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Deque.h)
include_directories(~/googletest/googletest/include)
link_directories(~/googletest/googletest/cmake-build-debug)
add_executable(Deque ${SOURCE_FILES} Deque.h)
target_link_libraries(Deque gtestd)