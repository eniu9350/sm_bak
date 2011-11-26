#ifndef _OSPSM_EL_
#define _OSPSM_EL_

#include <sys/epoll.h>

#define EL_EVENT_SETSIZE (1024*10)    /* Max number of fd supported */
#define EL_EVENT_NONE 0
#define EL_EVENT_READABLE 1
#define EL_EVENT_WRITABLE 2

struct _el_event_loop;

typedef void file_event_handler(struct _el_event_loop* el, int fd, void* data, int mask);

typedef struct _el_file_event {
	int mask;	/* one of AE_(READABLE|WRITABLE) */
	file_event_handler* rhandler;
	file_event_handler* whandler;
	void* data;
}el_file_event;

typedef struct _el_fired_event {
	int fd;
	int mask;
}el_fired_event;

typedef struct _el_event_loop	{
	int maxfd;
	int stopped;

	el_file_event events[EL_EVENT_SETSIZE];
	el_fired_event fired[EL_EVENT_SETSIZE];

	int epfd;
  struct epoll_event epevents[EL_EVENT_SETSIZE];
} el_event_loop;


el_event_loop* create_event_loop();
int add_file_event(el_event_loop* el, int fd, int mask, file_event_handler* handler, void* data);
int event_loop_step(el_event_loop* el);
int start_event_loop(el_event_loop* el);
#endif
