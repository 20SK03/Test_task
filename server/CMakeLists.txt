cmake_minimum_required(VERSION 3.10)
project(TimeServer)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(TimeServer server.cpp)

target_include_directories(TimeServer PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(TimeServer PRIVATE Boost::system)