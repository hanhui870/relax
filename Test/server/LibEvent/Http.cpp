#include <fstream>
#include <iostream>
#include <event.h>
#include <event2/http.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

using namespace std;
static void send_document_cb(struct evhttp_request *req, void *arg);

int main(int argc, char* argv[]) {
	struct event_base *base;
	struct evhttp *http;
	struct evhttp_bound_socket *handle;

	unsigned short port = 8082;
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return (1);

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Couldn't create an event_base: exiting\n");
		return 1;
	}

	http = evhttp_new(base);
	if (!http) {
		fprintf(stderr, "couldn't create evhttp. Exiting.\n");
		return 1;
	}

	evhttp_set_gencb(http, send_document_cb, argv[1]);

	/* Now we tell the evhttp what port to listen on */
	handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", port);
	if (!handle) {
		fprintf(stderr, "couldn't bind to port %d. Exiting.\n", (int) port);
		return 1;
	}

	return 0;
}
