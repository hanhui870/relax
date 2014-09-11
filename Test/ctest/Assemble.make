CPP=gcc
CFLAGS=-g
LIBS=-L/usr/local/lib  

Assemble.test:Assemble.o
	$(CPP) -o Assemble.exe Assemble.o  $(LIBS)
	
Assemble.s:Assemble.c
	$(CPP) -S Assemble.c $(CFLAGS)

Assemble.o:Assemble.s
	$(CPP) -c Assemble.s $(CFLAGS)

clean:
	rm Assemble.o Assemble.test