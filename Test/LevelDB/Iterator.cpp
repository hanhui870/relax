#include <iostream>
#include <leveldb/db.h>

int main(int argc, char **argv){
	leveldb::DB *db=NULL;
	leveldb::Options options;
	options.create_if_missing=false;

	leveldb::Status status = leveldb::DB::Open(options, "db.test", &db);
	if(!status.ok()){
		std::cerr<< status.ToString()<<std::endl;
		return 1;
	}

	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	for(it->SeekToFirst(); it->Valid(); it->Next()){
		std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
	}
	delete it;

	delete db;
	return 0;
}
