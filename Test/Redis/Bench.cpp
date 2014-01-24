#include <iostream>
#include <hiredis.h>

int main(int argc, char **argv){
	redisContext *c;
	redisReply *reply;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout((char*)"127.0.0.1", 6379, timeout);
	if (c->err) {
		printf("Connection error: %s\n", c->errstr);
		exit(1);
	}

	/* PING server */
	reply = redisCommand(c,"PING");
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);

	return 0;
}
