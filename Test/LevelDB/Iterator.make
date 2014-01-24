CPP=g++


Iterator.test:Iterator.o
	$(CPP) -o Iterator.test Iterator.o -lleveldb

Iterator.o:Iterator.cpp
	$(CPP) -c Iterator.cpp -O3

clean:
	rm Iterator.o Iterator.test