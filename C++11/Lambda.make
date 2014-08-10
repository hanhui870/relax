CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  

Lambda.test:Lambda.o
	$(CPP) -o Lambda.test Lambda.o  $(LIBS)

Lambda.o:Lambda.cpp
	$(CPP) -c Lambda.cpp -O3  $(CXXFLAGS)

clean:
	rm Lambda.o Lambda.test