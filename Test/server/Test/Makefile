CPP=g++


server.test: Server.o
	$(CPP) -o server.test Server.o -lboost_system
client.test: Client.o
	$(CPP) -o client.test Client.o -lboost_system

Server.o: Server.cpp
	$(CPP) -c Server.cpp
Client.o: Client.cpp
	$(CPP) -c Client.cpp

clean:
	rm Server.o server.test Client.o Client.test