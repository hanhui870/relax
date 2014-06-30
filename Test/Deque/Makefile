CPP=g++


server.test: main.o
	$(CPP) -o main.test main.o

main.o: main.cpp
	$(CPP) -c main.cpp

clean:
	rm main.o main.test