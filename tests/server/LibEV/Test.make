CPP=g++
CXXFLAGS=-I../../ -std=c++11
LIBS=-L/usr/local/lib  -levent

Test.test:Test.o
	$(CPP) -o Test.test Test.o  $(LIBS)

Test.o:Test.cpp
	$(CPP) -c Test.cpp -O3  $(CXXFLAGS)

clean:
	rm Test.o Test.test