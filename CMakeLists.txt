cmake_minimum_required(VERSION 3.9)
project(tinySTL)

set(CMAKE_CXX_STANDARD 17)

set(WORK_SPACE ${CMAKE_CURRENT_SOURCE_DIR})

# sources code
set(
    TINY_STL_SOURCES
)

# target
add_executable(
    tinySTL
    ${TINY_STL_SOURCES}
    main.cpp
)

# include
target_include_directories(
    tinySTL
    PRIVATE
    ${WORK_SPACE}
)