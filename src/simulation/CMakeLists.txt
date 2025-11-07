cmake_minimum_required(VERSION 3.10)

project(Simulation)

add_subdirectory(jsbsim)

add_library(simulation STATIC
    JSBSimInterface.h     
    JSBSimInterface.cpp
)

target_include_directories(simulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/jsbsim/src)

target_link_libraries(simulation PUBLIC libJSBSim)