CPP=g++
CXXFLAGS=-std=c++11
LIBS=

all:MoveSingal.test MoveArray.test

MoveSingal.test: MoveSingal.o
	$(CPP) -O3 -o MoveSingal.test MoveSingal.o $(LIBS)
MoveArray.test: MoveArray.o
	$(CPP) -O3 -o MoveArray.test MoveArray.o $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $< $(CXXFLAGS)

clean:
	rm test.o test.test