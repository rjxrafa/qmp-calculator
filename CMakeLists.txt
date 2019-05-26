cmake_minimum_required(VERSION 3.13)
project(qmp_calculator)

set(CMAKE_CXX_STANDARD 11)

set(sources qm_petrick.cpp)
set(include qm_petrick.h)


add_executable(qmp_calculator main.cpp
                ${sources}
                ${include})