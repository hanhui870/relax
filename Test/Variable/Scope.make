CPP=g++


Scope.test:Scope.o
	$(CPP) -o Scope.test Scope.o

Scope.o:Scope.cpp
	$(CPP) -c Scope.cpp -O3

clean:
	rm Scope.o Scope.test