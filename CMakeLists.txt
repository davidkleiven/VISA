# CMake lists
cmake_minimum_required(VERSION 3.6)

include_directories(include)
add_subdirectory(src)

find_package(SFML REQUIRED system window graphics network audio)
include_directories(SFML_INCLUDE_DIR)

find_package(Armadillo REQUIRED )
include_directories(ARMADILLO_INCLUDE_DIR)

# Add the examples
add_executable( exLinePlot.out Examples/exLinePlot.cpp )
target_link_libraries( exLinePlot.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exMexicanHat.out Examples/exMexicanHat.cpp)
target_link_libraries( exMexicanHat.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exSincFilter.out Examples/exSincFilter.cpp)
target_link_libraries( exSincFilter.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exSmallMatrix.out Examples/exSmallMatrix.cpp)
target_link_libraries( exSmallMatrix.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/src/libvisa.so)

# Install target
