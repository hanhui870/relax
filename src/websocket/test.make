CPP=g++

CXXFLAGS=-g -std=c++11 -gdwarf-2 -gstrict-dwarf

LIBS=-L/usr/local/lib  
OBJECTS=test.o
BINARY=test.exe

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CPP) -o $(BINARY) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(CPP) -c $(CXXFLAGS) $< -o $@
		
.PHONY:clean 
clean: 
	-rm -f $(OBJECTS) $(BINARY)
    