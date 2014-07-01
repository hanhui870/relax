CPP=g++
CXXFLAGS=-std=c++11

Regex.test: Regex.o
	$(CPP) -o Regex.test Regex.o

Regex.o: Regex.cpp
	$(CPP) -c Regex.cpp $(CXXFLAGS)

clean:
	rm Regex.o Regex.test