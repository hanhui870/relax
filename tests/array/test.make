CPP=g++

CXXFLAGS=-g -std=c++11 -DGTEST_LANG_CXX11=1 -U__STRICT_ANSI__

LIBS=-L/usr/local/lib 
OBJECTS= test.o
BINARY=test.exe

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CPP) -o $(BINARY) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(CPP) -c $(CXXFLAGS) $< -o $@ 
	
.PHONY:clean 
clean: 
	-rm -f $(OBJECTS) $(BINARY)
    