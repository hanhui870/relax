CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  

FutureWait.test:FutureWait.o
	$(CPP) -o FutureWait.test FutureWait.o  $(LIBS)

FutureWait.o:FutureWait.cpp
	$(CPP) -c FutureWait.cpp -O3  $(CXXFLAGS)

clean:
	rm FutureWait.o FutureWait.test