cmake_minimum_required(VERSION 3.13)
project(qmp_calculator)

set(CMAKE_CXX_STANDARD 11)

set(sources qm_petrick.cpp)
set(include qm_petrick.h)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++)
endif()

add_executable(qmp_calculator main.cpp
                ${sources}
                ${include})