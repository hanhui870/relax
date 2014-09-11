CPP=g++


UnixSocketClient.test:UnixSocketClient.o
	$(CPP) -o UnixSocketClient.test UnixSocketClient.o

UnixSocketClient.o:UnixSocketClient.cpp
	$(CPP) -c UnixSocketClient.cpp -O3

clean:
	rm UnixSocketClient.o UnixSocketClient.test