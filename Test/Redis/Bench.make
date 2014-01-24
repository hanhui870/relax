CPP=g++


Bench.test:Bench.o
	$(CPP) -o Bench.test Bench.o -lhiredis

Bench.o:Bench.cpp
	$(CPP) -c Bench.cpp -O3

clean:
	rm Bench.o Bench.test