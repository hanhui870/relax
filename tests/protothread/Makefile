CPP=gcc
CFLAGS=-g
LIBS=

test.exe:test.o
	$(CPP) -o test.exe test.o  $(LIBS)
	
test.s:test.c
	$(CPP) -S test.c $(CFLAGS)

test.o:test.s
	$(CPP) -c test.s $(CFLAGS)

clean:
	rm test.o test.exe