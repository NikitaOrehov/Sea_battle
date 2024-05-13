cmake_minimum_required(VERSION 3.10)
project(sea_battle LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_executable(main main.cpp struct.h)

include_directories(field)
add_subdirectory(FIELD)

include_directories(player)
add_subdirectory(PLAYERS)

include_directories(ship)
add_subdirectory(SHIPS)
target_link_libraries(main field player ship)