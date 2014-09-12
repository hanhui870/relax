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

	std::string key("hanhui99");

	if(argc==2){
		key=std::string(argv[1]);
	}

	std::string value;
	std::cout<<"fetch value for key:"<<key<<std::endl;
	status =db->Get(leveldb::ReadOptions(), key, &value);
	if(status.ok()){
		std::cout<<"LevelDb hanhui's Value:"<<value<<std::endl;
	}else{
		std::cerr<< status.ToString()<<std::endl;
	}
	delete db;
	return 0;
}
