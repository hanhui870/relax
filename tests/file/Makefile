CPP=g++
CXXFLAGS= -std=c++11
LIBS=

test.bin: test.o
	$(CPP) -O3 -o test.test test.o $(LIBS)

test.o: test.cpp
	$(CPP) -c test.cpp $(CXXFLAGS)

clean:
	rm test.o test.test