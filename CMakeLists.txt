cmake_minimum_required(VERSION 3.12)
project(sorting_trees_and_posting_web)

set(CMAKE_CXX_STANDARD 14)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    set(EXECUTABLE_OUTPUT_PATH "C:/games/open server ultimate/OSPanel/domains/sorting")
    add_executable(sorting_trees_and_posting_web main.cpp functions.h functions.cpp trees.h trees.cpp)
    set_target_properties(sorting_trees_and_posting_web PROPERTIES OUTPUT_NAME "sorting" SUFFIX ".cgi")
else()
    add_executable(sorting_trees_and_posting_web main.cpp functions.h functions.cpp trees.h trees.cpp)
endif()