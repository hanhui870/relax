#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <leveldb/db.h>
using namespace std;

int main(int argc, char **argv){
	leveldb::DB *db=NULL;
	leveldb::Options options;
	options.create_if_missing=true;

	//db.test is a directory.
	leveldb::Status status = leveldb::DB::Open(options, "db.test", &db);
	if(!status.ok()){
		std::cerr<< status.ToString()<<std::endl;
		return 1;
	}

	std::string name("hanhui");
	std::string key;
	//writes 1M, 94 time costs:4.555s use diskspace 41M
	//公司I3/8G开发机 consts:8.843s use diskspace 41M 基于cygwin
	for(int iter=0; iter<1000000; iter++){
		char temp[100];
		std::sprintf(temp, "%d", iter);
		//std::cout<<temp<<std::endl;
		key.assign(name+temp);
		//std::cout<<key<<std::endl;
		db->Put(leveldb::WriteOptions(), key, key+temp+"A good man!");
	}

	delete db;
	return 0;
}
