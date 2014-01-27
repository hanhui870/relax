CPP=g++


Process.test:Process.o
	$(CPP) -o Process.test Process.o

Process.o:Process.cpp
	$(CPP) -c Process.cpp -O3

clean:
	rm Process.o Process.test