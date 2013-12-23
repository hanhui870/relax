INCULDES=-I/usr/include/mysql
CPP=g++


mysqlpp.test:MysqlPP.o
	$(CPP) -o mysqlpp.test MysqlPP.o -lmysqlpp

MysqlPP.o:MysqlPP.cpp
	$(CPP) -c MysqlPP.cpp $(INCULDES)

clean:
	rm MysqlPP.o mysqlpp.test