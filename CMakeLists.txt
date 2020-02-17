cmake_minimum_required(VERSION 3.5)
project(JSSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(JSSP_HEADER_FILES
        include/solution.h
        include/algorithm.h
        include/bee_colony.h
        include/jssp.h
        include/problem.h)

set(JSSP_SOURCE_FILES
        src/main.cpp
        src/solution.cpp
        src/bee_colony.cpp
        src/jssp.cpp
        src/algorithm.cpp
        src/problem.cpp)

add_executable(${PROJECT_NAME} ${JSSP_HEADER_FILES} ${JSSP_SOURCE_FILES})