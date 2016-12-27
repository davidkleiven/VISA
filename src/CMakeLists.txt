set(SOURCES visualizer.cpp visualizer1D.cpp lowPassFilter.cpp fifoBuffer.cpp colormaps.cpp gaussianKernel.cpp windowHandler.cpp )

# Create a shared library
add_library( visa SHARED ${SOURCES})

# Install the library
install( TARGETS visa DESTINATION ${INSTALL_LIB_DIR})
#install( EXPORT visa DESTINATION ${INSTALL_LIB_DIR})
