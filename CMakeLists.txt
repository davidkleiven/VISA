# CMake lists
cmake_minimum_required(VERSION 3.6)
project(VISA)

# Install paths
set( INSTALL_LIB_DIR "/usr/local/lib" )
set( INSTALL_INCLUDE_DIR "/usr/local/include" )
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(include)
add_subdirectory(src)

find_package(SFML REQUIRED system window graphics network audio)
include_directories(SFML_INCLUDE_DIR)

find_package(Armadillo REQUIRED )
include_directories(ARMADILLO_INCLUDE_DIR)

add_subdirectory(unittest)
# Add the examples
add_executable( exLinePlot.out Examples/exLinePlot.cpp )
target_link_libraries( exLinePlot.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exMexicanHat.out Examples/exMexicanHat.cpp)
target_link_libraries( exMexicanHat.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exSincFilter.out Examples/exSincFilter.cpp)
target_link_libraries( exSincFilter.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exSmallMatrix.out Examples/exSmallMatrix.cpp)
target_link_libraries( exSmallMatrix.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/src/libvisa.so)
target_link_libraries( exSmallMatrix.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} visa)

add_executable( waveOnMembrane.out Examples/waveOnMembrane.cpp)
target_link_libraries( waveOnMembrane.out ${SFML_LIBRARIES} libvisa.so)

# Install target

set( HEADERFILES include/colormaps.hpp include/fifoBuffer.hpp include/gaussianKernel.hpp include/lowPassFilter.hpp include/lowPassFilter.tpp
include/visa.hpp include/visualizer.hpp include/visualizer1D.hpp include/windowHandler.hpp include/armaGetter.hpp)

install( FILES ${HEADERFILES} DESTINATION ${INSTALL_INCLUDE_DIR}/visa )

enable_testing()
add_test(NAME visaTest COMMAND ./unittest/alltest.out )
