#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
using namespace std;

int main(int argc, char* argv[]){
	const char* sockPath="/home/bruce/test/server.sock";
	int socketFd;
	const int backlog=10;
	const int bufferSize=1000;
	struct sockaddr_un address;
	char buffer[bufferSize];

	socketFd=socket(AF_UNIX, SOCK_STREAM, 0);
	if(-1==socketFd){
		cerr<<"socket create error."<<endl;
		return -1;
	}

	memset(&address, 0, sizeof(struct sockaddr_un));
	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, sockPath, sizeof(address.sun_path) - 1);

	if(connect(socketFd, (struct sockaddr *)&address, sizeof(struct sockaddr_un))==-1){
		cerr<<"failed to unix socket error."<<endl;
		return -1;
	}

	cout<<"socket connected."<<endl;


	for( ; ; ){
		cout<<"Please input some words to send:"<<endl;
		getline(cin, buffer);

		size_t len=0;
		if((len=strlen(buffer))>0){
			if(buffer=="exit"){
				break;
			}
			write(socketFd, buffer, len);
		}
	}

	close(socketFd);
	//delete after use it
	unlink(sockPath);
	return 0;
}
