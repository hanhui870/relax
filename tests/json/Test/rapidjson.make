CPP=g++

rapidjson.test:RapidJson.o
	$(CPP) -o rapidjson.test RapidJson.o

RapidJson.o:RapidJson.cpp
	$(CPP) -c RapidJson.cpp -O3

clean:
	rm RapidJson.o rapidjson.test