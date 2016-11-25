cmake_minimum_required (VERSION 2.8.11)
project (Threads)

find_package (Threads)

set(PROJECT_CFLAGS "-Wall -std=c++14")

add_executable (threads Threads.cpp  ThreadPool.cpp Chrono.hpp ThreadPool.hpp)
set_target_properties(threads PROPERTIES COMPILE_FLAGS "${PROJECT_CFLAGS}")
target_link_libraries (threads ${CMAKE_THREAD_LIBS_INIT})

