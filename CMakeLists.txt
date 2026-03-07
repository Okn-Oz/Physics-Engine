cmake_minimum_required(VERSION 3.28)
project(PhysicsEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(PhysicsEngine main.cpp utils.cpp)

target_link_libraries(PhysicsEngine PRIVATE SFML::Graphics SFML::Window)
