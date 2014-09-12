CPP=g++


Float.test:Float.o
	$(CPP) -o Float.test Float.o

Float.o:Float.cpp
	$(CPP) -c Float.cpp -O3

clean:
	rm Float.o Float.test