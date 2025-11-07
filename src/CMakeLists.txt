cmake_minimum_required(VERSION 3.10)

project(FCU)

add_subdirectory(simulation)

add_executable(fcu
    main.cpp
)

target_include_directories(fcu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/simulation)

target_link_libraries(fcu PUBLIC simulation)