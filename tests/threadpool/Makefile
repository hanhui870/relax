CPP=g++

thread.exe:thread.o
	$(CPP) -o thread.exe thread.o -lPocoFoundationd 

thread.o:thread.cpp
	$(CPP) -c thread.cpp -g

clean:
	rm thread.o thread.exe