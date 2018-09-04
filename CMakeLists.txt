# CMake lists
cmake_minimum_required(VERSION 3.6)
project(VISA)

list(APPEND CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
list(APPEND CMAKE_MODULE_PATH ${SFML_DIR})

set( CMAKE_CXX_STANDARD 11 )
add_definitions( -DARMA_NO_DEBUG ) # Disable Armadillo debug checks

# Install paths
set( INSTALL_LIB_DIR "/usr/local/lib" )
set( INSTALL_INCLUDE_DIR "/usr/local/include" )
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(OpenMP)
if ( OPENMP_FOUND )
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif()

include_directories(include)
add_subdirectory(src)

# find_package(SFML REQUIRED network audio graphics window system)
find_package(SFML REQUIRED COMPONENTS graphics window audio network system)
include_directories(SFML_INCLUDE_DIR)

find_package(Armadillo REQUIRED )
include_directories(ARMADILLO_INCLUDE_DIR)

MESSAGE(STATUS ${SFML_LIBRARIES})
#add_subdirectory(unittest)
# Add the examples
add_executable( exLinePlot.out EXCLUDE_FROM_ALL Examples/exLinePlot.cpp )
target_link_libraries( exLinePlot.out ${SFML_LIBRARIES} libvisa.so)

add_executable( exMexicanHat.out EXCLUDE_FROM_ALL Examples/exMexicanHat.cpp)
# target_link_libraries( exMexicanHat.out ${SFML_LIBRARIES} libvisa.so)
target_link_libraries( exMexicanHat.out libvisa.so ${SFML_LIBRARIES})

add_executable( exSincFilter.out EXCLUDE_FROM_ALL Examples/exSincFilter.cpp)
target_link_libraries( exSincFilter.out libvisa.so ${SFML_LIBRARIES})

add_executable( exSmallMatrix.out EXCLUDE_FROM_ALL Examples/exSmallMatrix.cpp)
target_link_libraries( exSmallMatrix.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/src/libvisa.so)
target_link_libraries( exSmallMatrix.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} visa)

add_executable( overlay.out EXCLUDE_FROM_ALL Examples/overlay.cpp)
target_link_libraries( overlay.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/src/libvisa.so)
target_link_libraries( overlay.out ${SFML_LIBRARIES} ${ARMADILLO_LIBRARY} visa)

add_executable(waveOnMembrane.out Examples/waveOnMembrane.cpp)
add_dependencies(waveOnMembrane.out visa)
target_link_libraries( waveOnMembrane.out ${CMAKE_CURRENT_SOURCE_DIR}/src/libvisa.so ${SFML_LIBRARIES})

# Install target
set( HEADERFILES include/colormaps.hpp include/fifoBuffer.hpp include/gaussianKernel.hpp include/lowPassFilter.hpp include/lowPassFilter.tpp
include/visa.hpp include/visualizer.hpp include/visualizer1D.hpp include/windowHandler.hpp include/armaGetter.hpp)

install( FILES ${HEADERFILES} DESTINATION ${INSTALL_INCLUDE_DIR}/visa )
enable_testing()
add_test(NAME visaTest COMMAND ./unittest/alltest.out )
