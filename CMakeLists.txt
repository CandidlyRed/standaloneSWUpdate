cmake_minimum_required(VERSION 3.10)

project(SwUpdateProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(swupdate/include)

set(SWUPDATE_SOURCES
    swupdate/ipc/network_ipc-if.c
    swupdate/ipc/network_ipc.c
)

add_executable(SwUpdateProject workspace.cpp ${SWUPDATE_SOURCES})

add_subdirectory(jsoncpp)

target_link_libraries(SwUpdateProject jsoncpp_lib)
