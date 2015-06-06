cmake_minimum_required(VERSION 3.2)

add_subdirectory(third_party)

add_executable(still_broken src/still_broken.cc)
set_property(TARGET still_broken PROPERTY CXX_STANDARD 11)
target_link_libraries(still_broken curl)

add_executable(broken_link_finder src/broken_link_finder.cc)
set_property(TARGET broken_link_finder PROPERTY CXX_STANDARD 11)
target_link_libraries(broken_link_finder curl)
