CPP=g++


LevelDB.test:LevelDB.o
	$(CPP) -o LevelDB.test LevelDB.o -lleveldb

LevelDB.o:LevelDB.cpp
	$(CPP) -c LevelDB.cpp -O3

clean:
	rm LevelDB.o LevelDB.test