CPP=g++

CXXFLAGS=-g -std=c++11

LIBS=-L/usr/local/lib  -lprotobuf

all: proto add list

proto: 
	protoc --cpp_out=. --python_out=. addressbook.proto
	
add: add_person.o addressbook.pb.o
	$(CPP) -o add.exe add_person.o addressbook.pb.o $(LIBS)
	
list: list_people.o addressbook.pb.o	
	$(CPP) -o list.exe list_people.o addressbook.pb.o $(LIBS)

add_person.o: add_person.cc
	$(CPP) -c  add_person.cc $(CXXFLAGS)

list_people.o: list_people.cc
	$(CPP) -c  list_people.cc $(CXXFLAGS)

addressbook.pb.o: addressbook.pb.cc
	$(CPP) -c  addressbook.pb.cc $(CXXFLAGS)
	
.PHONY:clean 
clean: 
	
    