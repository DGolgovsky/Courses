project(final)
cmake_minimum_required(VERSION 2.8)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE, "RELEASE")
endif()
set(SRC_LIST main.c)
add_executable(${PROJECT_NAME} ${SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-pthread" COMPILE_FLAGS "-Wall -pthread" )
