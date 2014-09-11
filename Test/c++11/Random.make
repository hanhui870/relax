CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  

Random.test:Random.o
	$(CPP) -o Random.test Random.o  $(LIBS)

Random.o:Random.cpp
	$(CPP) -g -c Random.cpp -O3  $(CXXFLAGS)

clean:
	rm Random.o Random.test