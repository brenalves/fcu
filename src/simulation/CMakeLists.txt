cmake_minimum_required(VERSION 3.20)

project(gravitumsimulation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(jsbsim)

add_library(gravitumsimulation STATIC
    JSBSimInterface.cpp
    JSBSimInterface.h
)

target_include_directories(gravitumsimulation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/jsbsim/src
)

target_link_directories(gravitumsimulation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/jsbsim/src
)

target_link_libraries(gravitumsimulation PUBLIC
    jsbsim
)
