cmake_minimum_required(VERSION 3.6)

find_package(GTest REQUIRED)
include_directories( GTEST_INCLUDE_DIRS )
add_executable( alltest.out maintest.cpp testFifo.cpp)
target_link_libraries( alltest.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} ${GTEST_BOTH_LIBRARIES} visa pthread)
