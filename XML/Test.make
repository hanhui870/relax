CPP=g++


Test.test:Test.o
	$(CPP) -o Test.test Test.o

Test.o:Test.cpp
	$(CPP) -c Test.cpp -O3

clean:
	rm Test.o Test.test