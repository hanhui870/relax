#include <iostream>
#include <leveldb/db.h>
using namespace std;

int main(int argc, char **argv){
	leveldb::DB *db=NULL;
	leveldb::Options options;
	options.create_if_missing=true;

	//指定的testdb是个目录
	leveldb::Status status = leveldb::DB::Open(options, "db.test", &db);
	if(!status.ok()){
		cerr<< status.ToString()<<endl;
		return 1;
	}

	std::string value;
	status =db->Get(leveldb::ReadOptions(), "hanhui", &value);
	if(status.ok()){
		cout<<"LevelDb hanhui's Value:"<<value<<endl;
	}
	delete db;
	return 0;
}
