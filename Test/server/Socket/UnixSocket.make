CPP=g++


UnixSocket.test:UnixSocket.o
	$(CPP) -o UnixSocket.test UnixSocket.o

UnixSocket.o:UnixSocket.cpp
	$(CPP) -c UnixSocket.cpp -O3

clean:
	rm UnixSocket.o UnixSocket.test