cmake_minimum_required(VERSION 3.10)
project(pq)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(pq main.cpp thread_flowGenerator.cpp thread_trafficClassificator.cpp thread_scheduler.cpp common.cpp)