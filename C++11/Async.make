CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  

Async.test:Async.o
	$(CPP) -o Async.test Async.o  $(LIBS)

Async.o:Async.cpp
	$(CPP) -c Async.cpp -O3  $(CXXFLAGS)

clean:
	rm Async.o Async.test