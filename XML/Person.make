CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  -lxml2 -liconv -lz

Person.test:Person.o
	$(CPP) -o Person.test Person.o  $(LIBS)

Person.o:Person.cpp
	$(CPP) -c Person.cpp -O3  $(CXXFLAGS)

clean:
	rm Person.o Person.test