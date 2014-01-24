#include <iostream>
#include <leveldb/db.h>

int main(int argc, char **argv){
	leveldb::DB *db=NULL;
	leveldb::Options options;
	options.create_if_missing=true;

	leveldb::Status status = leveldb::DB::Open(options, "db.test", &db);
	if(!status.ok()){
		std::cerr<< status.ToString()<<std::endl;
		return 1;
	}

	std::string value;
	status =db->Get(leveldb::ReadOptions(), "hanhui", &value);
	if(status.ok()){
		std::cout<<"LevelDb hanhui's Value:"<<value<<std::endl;
	}
	delete db;
	return 0;
}
