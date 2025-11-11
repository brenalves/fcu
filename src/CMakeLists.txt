cmake_minimum_required(VERSION 3.20)

add_subdirectory(jsbsim)

project(fcu)

add_executable(fcu main.cpp pid.h pid.cpp)

target_include_directories(fcu PRIVATE jsbsim/src)
target_link_libraries(fcu PRIVATE libJSBSim)

add_custom_command(
    TARGET fcu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/jsbsim/aircraft
        $<TARGET_FILE_DIR:fcu>/aircraft

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/jsbsim/engine
        $<TARGET_FILE_DIR:fcu>/engine

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/jsbsim/systems
        $<TARGET_FILE_DIR:fcu>/systems
)