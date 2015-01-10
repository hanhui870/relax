
CPP=g++


Int.test:Int.o
	$(CPP) -o Int.test Int.o

Int.o:Int.cpp
	$(CPP) -c Int.cpp -O3

clean:
	rm Int.o Int.test