set(SOURCES visualizer.cpp visualizer1D.cpp lowPassFilter.cpp fifoBuffer.cpp colormaps.cpp gaussianKernel.cpp windowHandler.cpp )

# Create a shared library
add_library( visa SHARED ${SOURCES})
