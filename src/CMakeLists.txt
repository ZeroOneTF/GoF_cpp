cmake_minimum_required(VERSION 3.9)

add_library(gof_cpp "")

target_sources(
    gof_cpp
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/corona10/decorator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/corona10/buffered_reader.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
    gof_cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)