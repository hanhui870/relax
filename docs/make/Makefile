all: test.exe

clean:
    rm test.o test.exe

hello.exe: test.o
    g++ -g -o test test.o

main.o:
    g++ -c -g test.cpp