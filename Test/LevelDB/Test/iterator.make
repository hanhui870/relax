CPP=g++


iterator.test:iterator.o
	$(CPP) -o iterator.test iterator.o -lleveldb

iterator.o:iterator.cpp
	$(CPP) -c iterator.cpp -O3

clean:
	rm iterator.o iterator.test