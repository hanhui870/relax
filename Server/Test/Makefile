CPP=g++


server.test:Server.o
	$(CPP) -o server.test Server.o -lserver_linux-gcc-4.8.2_libmt

Server.o:Server.cpp
	$(CPP) -c Server.cpp

clean:
	rm Server.o server.test