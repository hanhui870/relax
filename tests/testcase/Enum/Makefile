CPP=g++

test.test:Test.o
	$(CPP) -o test.test Test.o

Test.o:Test.cpp
	$(CPP) -c Test.cpp -O3

clean:
	rm Test.o test.test