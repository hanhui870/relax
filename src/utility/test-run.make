CPP=g++

CXXFLAGS=-O3 -std=c++11 -DGTEST_LANG_CXX11=1 -U__STRICT_ANSI__ -I../../include

LIBS=-L/usr/local/lib  -lboost_timer -lboost_system -lPocoFoundation
OBJECTS=number_helper.o ini_helper.o time_helper.o env_helper.o string_helper.o string_parser.o ../relax/relax.o test-run.o
BINARY=test-run.exe

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CPP) -o $(BINARY) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(CPP) -c $(CXXFLAGS) $< -o $@ 
	
.PHONY:clean 
clean: 
	-rm -f $(OBJECTS) $(BINARY)
    