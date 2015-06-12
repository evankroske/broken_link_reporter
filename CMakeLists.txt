cmake_minimum_required(VERSION 3.2)

add_subdirectory(third_party)

add_executable(still_broken src/still_broken.cc)
set_property(TARGET still_broken PROPERTY CXX_STANDARD 11)
target_link_libraries(still_broken curl)

add_executable(broken_link_finder src/broken_link_finder.cc)
set_property(TARGET broken_link_finder PROPERTY CXX_STANDARD 11)
target_link_libraries(broken_link_finder curl)

include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

add_executable(run_tests test/http_client_test.cc)
set_property(TARGET run_tests PROPERTY CXX_STANDARD 11)
target_link_libraries(run_tests gtest_main)
