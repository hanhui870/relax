#include <iostream>
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

	//We can't bind a socket to an existing pathname (bind() fails with the error EADDRINUSE).
	if(bind(socketFd, (struct sockaddr *)&address, sizeof(struct sockaddr_un))==-1){
		cerr<<"bind socket address error."<<endl;
		return -1;
	}

	cout<<"socket created. listening..."<<endl;

	if(-1==listen(socketFd, backlog)){
		cerr<<"failed to start listening."<<endl;
		return -1;
	}

	for( ; ; ){
		int clientFd=accept(socketFd, NULL, NULL);
		if(-1==clientFd){
			cerr<<"failed to accept."<<endl;
			return -1;
		}

		size_t numRead=0;
		while((numRead=read(clientFd, buffer, bufferSize))>0){
			cout<<"Server get:"<<buffer<<endl;
			string a(buffer);
			if(a=="exit"){
				cout<<"Server terminated."<<endl;
				goto end;
			}
			memset(buffer, 0, bufferSize);
		}

		if(-1==numRead){
			cerr<<"read error."<<endl;
			return -1;
		}
	}

end:
	close(socketFd);
	//delete after use it
	unlink(sockPath);
	return 0;
}
