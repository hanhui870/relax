CPP=g++


get.test:get.o
	$(CPP) -o get.test get.o -lleveldb

get.o:get.cpp
	$(CPP) -c get.cpp -O3

clean:
	rm get.o get.test