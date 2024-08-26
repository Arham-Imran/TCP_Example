cmake_minimum_required(VERSION 3.5.0)
project(TCP_Example VERSION 0.1.0 LANGUAGES C CXX)

add_executable(TCP_Client TCP_Client.cpp)
add_executable(TCP_Server TCP_Server.cpp)

target_link_libraries(TCP_Client ws2_32)
target_link_libraries(TCP_Server ws2_32)
