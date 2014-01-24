#include <iostream>
#include <leveldb/db.h>
using namespace std;

int main(int argc, char **argv){
	leveldb::DB *db=NULL;
	leveldb::Options options;
	options.create_if_missing=true;

	//指定的db.test是个目录
	leveldb::Status status = leveldb::DB::Open(options, "db.test", &db);
	if(!status.ok()){
		std::cerr<< status.ToString()<<std::endl;
		return 1;
	}

	std::string name("hanhui");
	std::string key;
	for(int iter=0; iter<1000000; iter++){
		key.append(name+static_cast<std::string>(iter));
		db->Put(leveldb::WriteOptions(), name, "A good man!");
	}

	delete db;
	return 0;
}
