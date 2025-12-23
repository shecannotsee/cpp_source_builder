cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "asio-1.28.0")
set(CMAKE_CXX_FLAGS "-g")
project(${PROJECT_NAME})

########################################################################################################################
# import asio
set(_asio_path "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/asio-1.28.0")
set(asio_include_dir "${_asio_path}/include")
set(asio_lib_dir)
set(asio_link_libs)
########################################################################################################################

# include
include_directories(${asio_include_dir})
# lib
link_directories()

file(GLOB_RECURSE SRC_SERVER "${CMAKE_SOURCE_DIR}/server.cpp")
file(GLOB_RECURSE SRC_CLIENT "${CMAKE_SOURCE_DIR}/client.cpp")
add_executable(${PROJECT_NAME}_server ${SRC_SERVER})
add_executable(${PROJECT_NAME}_client ${SRC_CLIENT})

# link
target_link_libraries(${PROJECT_NAME}_server "-pthread")
target_link_libraries(${PROJECT_NAME}_client "-pthread")