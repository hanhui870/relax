CPP=g++


string.exe:string.o
	$(CPP) -o string.exe string.o

string.o:string.cpp
	$(CPP) -c string.cpp -O3

clean:
	rm string.o string.exe