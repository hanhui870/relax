CPP=g++
#gtest暂时不支持-std=c++11 flag
CXXFLAGS=-g
LIBS=-L/usr/local/lib   -lgtest -lgtest_main
LIBOBJECTS=algorithm.o test.o
BINARY=test.exe

all: $(BINARY)

$(BINARY): $(LIBOBJECTS)
	$(CPP) -o test.exe $(LIBOBJECTS) $(LIBS)

$(objects): %.o: %.c 
	$(CPP) -c $(CXXFLAGS) $< -o $@ 
	
.PHONY:clean 
clean: 
	-rm $(LIBOBJECTS) $(BINARY)
    