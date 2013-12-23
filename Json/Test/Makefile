CPP=g++


json.test:Json.o
	$(CPP) -o json.test Json.o -ljson_linux-gcc-4.8.2_libmt

Json.o:Json.cpp
	$(CPP) -c Json.cpp -O3

clean:
	rm Json.o json.test