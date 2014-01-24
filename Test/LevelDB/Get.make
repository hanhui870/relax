CPP=g++


Get.test:Get.o
	$(CPP) -o Get.test Get.o -lleveldb

Get.o:Get.cpp
	$(CPP) -c Get.cpp -O3

clean:
	rm Get.o Get.test