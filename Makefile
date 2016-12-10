IDIR=include
ODIR=obj
SDIR=src
TESTDIR=unittest
EXDIR=Examples

SOURCES := visualizer.cpp visualizer1D.cpp lowPassFilter.cpp fifoBuffer.cpp colormaps.cpp gaussianKernel.cpp windowHandler.cpp
TESTS := maintest.cpp testFifo.cpp
TEST_OBJECTS := ${TESTS:%.cpp=%.o}
TEST_OBJECTS := $(addprefix ${ODIR}/, ${TEST_OBJECTS})
OBJECTS := ${SOURCES:%.cpp=%.o}
SOURCES := $(addprefix ${SDIR}/, ${SOURCES})
OBJECTS := $(addprefix ${ODIR}/, ${OBJECTS})
GRAPHLIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean

lib: ${OBJECTS}
	g++  -std=c++11 $^ -fPIC -shared -o libvisa.so

alltest.out: ${OBJECTS} ${TEST_OBJECTS}
	g++ $^ -o $@ ${GRAPHLIBS} -lgtest -lgtest_main -lpthread

exSincFilter.out: ${ODIR}/exSincFilter.o ${OBJECTS}
	g++ $^ -o $@ ${GRAPHLIBS}

exMexicanHat.out: ${ODIR}/exMexicanHat.o
	g++ $^ -o $@ ${GRAPHLIBS} -Wl,-rpath,./ -L ./ -larmadillo -lvisa

exSmallMatrix.out: ${ODIR}/exSmallMatrix.o
	g++ $^ -o $@ ${GRAPHLIBS} -Wl,-rpath,./ -L ./ -larmadillo -lvisa

${ODIR}/%.o: ${SDIR}/%.cpp
	g++ -std=c++11 -fPIC -MMD -c $< -o $@ -I ${IDIR}

${ODIR}/%.o: ${TESTDIR}/%.cpp
	g++ -std=c++11 -fPIC -MMD -c $< -o $@ -I ${IDIR}

${ODIR}/%.o: ${EXDIR}/%.cpp
	g++ -std=c++11 -fPIC -MMD -c $< -o $@ -I ${IDIR}
clean:
	rm ${ODIR}/*.o
