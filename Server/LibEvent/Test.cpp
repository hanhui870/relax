#include <fstream>
#include <iostream>
#include <event.h>

using namespace std;

static void
signal_cb(evutil_socket_t fd, short event, void *arg)
{
	struct event *signal = static_cast<struct event *>(arg);

	printf("%s: got signal %d\n", __func__, EVENT_SIGNAL(signal));
}

int main(int argc, char* argv[]){
	struct event signal_instance;
	struct event_base* base;

	base = event_base_new();
	event_assign(&signal_instance, base, SIGINT, EV_SIGNAL|EV_PERSIST, signal_cb,
		    &signal_instance);

	event_add(&signal_instance, NULL);

	event_base_dispatch(base);
	event_base_free(base);

    return 0;
}
