#include <iostream>
#include <cstdio>
#include <hiredis.h>

int main(int argc, char **argv){
	redisContext *c;
	redisReply *reply;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout((char*)"127.0.0.1", 6379, timeout);
	if (c->err) {
		printf("Connection error: %s\n", c->errstr);
		return 1;
	}

	/* PING server */
	reply =static_cast<redisReply *>(redisCommand(c,"PING"));
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);

	std::string name("hanhui");
	std::string key;

	//use db 5 for test
	reply =static_cast<redisReply *>(redisCommand(c,"select 5"));
	//printf("SET: %s\n", reply->str);
	freeReplyObject(reply);

	//no batch:writes 1M, 94 time costs:real	1m6.812s, 14967.3711qps. Used_memory_human:130.56M
	//batch:wrap 1M entries, time cousts:real	1m6.323s, without obvious effect. May need small size of batch.
	//reply =static_cast<redisReply *>(redisCommand(c,"multi"));
	//freeReplyObject(reply);

	for(int iter=0; iter<1000000; iter++){
		char temp[100];
		std::sprintf(temp, "%d", iter);
		//std::cout<<temp<<std::endl;
		key.assign(name+temp);
		//std::cout<<key<<std::endl;

		std::string value=key+temp+"A good man!";
		reply =static_cast<redisReply *>(redisCommand(c,"SET %s %s", key.c_str(), value.c_str()));
		//printf("SET: %s\n", reply->str);

		//comment it for memory leak test.
		freeReplyObject(reply);
	}

	//reply =static_cast<redisReply *>(redisCommand(c,"exec"));
	//freeReplyObject(reply);

	delete c;
	return 0;
}
