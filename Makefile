IDIR=include
ODIR=obj
SDIR=src

SOURCES := visualizer.cpp visualizer1D.cpp sincFilter.cpp fifoBuffer.cpp
OBJECTS := ${SOURCES:%.cpp=%.o}
SOURCES := $(addprefix ${SDIR}/, ${SOURCES})
OBJECTS := $(addprefix ${ODIR}/, ${OBJECTS})
GRAPHLIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean

lib: ${OBJECTS}
	g++  -std=c++11 $^ -fPIC -shared -o libvisa.so

${ODIR}/%.o: ${SDIR}/%.cpp
	g++ -std=c++11 -fPIC -MMD -c $< -o $@ -I ${IDIR}

clean:
	rm ${ODIR}/*.o
