cmake_minimum_required(VERSION 3.9)

add_executable(
    test_corona10
    test_corona10.cpp
    )

target_link_libraries(
    test_corona10
    gtest_main
    gof_cpp
    )

add_test(
  NAME
    gof_cpp_test_corona10
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/test_corona10
  )