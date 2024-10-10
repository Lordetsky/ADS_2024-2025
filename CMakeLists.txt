cmake_minimum_required(VERSION 3.28)
project(Aboba)

set(CMAKE_CXX_STANDARD 17)

find_package(Python3 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(Python3_EXECUTABLE "/opt/homebrew/Cellar/python@3.12/3.12.3/bin/python3")


add_subdirectory(Sorts)
add_subdirectory(Structures)
add_subdirectory(Contest_1)
