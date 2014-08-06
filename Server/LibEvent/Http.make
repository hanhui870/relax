CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  -levent

Http.test:Http.o
	$(CPP) -o Http.test Http.o  $(LIBS)

Http.o:Http.cpp
	$(CPP) -c Http.cpp -O3  $(CXXFLAGS)

clean:
	rm Http.o Http.test