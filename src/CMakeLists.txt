cmake_minimum_required(VERSION 3.10)

project(FCU)

add_subdirectory(simulation)

add_executable(fcu
    main.cpp
)

target_include_directories(fcu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/simulation)

target_link_libraries(fcu PUBLIC simulation)

add_custom_command(
    TARGET fcu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/simulation/jsbsim/aircraft
        $<TARGET_FILE_DIR:fcu>/simulation/aircraft
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/simulation/jsbsim/engine
        $<TARGET_FILE_DIR:fcu>/simulation/engine
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/simulation/jsbsim/systems
        $<TARGET_FILE_DIR:fcu>/simulation/systems
)