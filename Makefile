IDIR=include
ODIR=obj
SDIR=src
TESTDIR=unittest

SOURCES := visualizer.cpp visualizer1D.cpp sincFilter.cpp fifoBuffer.cpp
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

${ODIR}/%.o: ${SDIR}/%.cpp
	g++ -std=c++11 -fPIC -MMD -c $< -o $@ -I ${IDIR}

${ODIR}/%.o: ${TESTDIR}/%.cpp
	g++ -std=c++11 -fPIC -MMD -c $< -o $@ -I ${IDIR}

alltest.out: ${OBJECTS} ${TEST_OBJECTS}
	g++ -o $^ -o $@ ${GRAPHLIBS} -lgtest -lgtest_main -lpthread

clean:
	rm ${ODIR}/*.o
