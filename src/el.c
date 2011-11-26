#include "el.h"

#include <sys/epoll.h>

el_event_loop* create_event_loop()
{
	int i;
	el_event_loop* el = (el_event_loop*)malloc(sizeof(el_event_loop));
	if(!el)	{
		printf("create el error, malloc failed!\n");
		return 0;
	}

	el->stopped = 0;

	el->epfd = epoll_create(1024);
	if(el->epfd==-1)	{
		printf("epoll create error!\n");
		return 0;
	}

	for(i=0;i<EL_EVENT_SETSIZE;i++)	{
		el->events[i].mask = EL_EVENT_NONE;
	}

	return el;
}

int add_file_event(el_event_loop* el, int fd, int mask, file_event_handler* handler, void* data)
{

	struct epoll_event ee;

	int op = el->events[fd].mask == EL_EVENT_NONE?EPOLL_CTL_ADD:EPOLL_CTL_MOD;

	el_file_event* fe = &el->events[fd];

	ee.events = 0;

	mask |= el->events[fd].mask;

	if(mask&EL_EVENT_READABLE)	{
		ee.events |= EPOLLIN;
	}
	if(mask&EL_EVENT_WRITABLE)	{
		ee.events |= EPOLLOUT;
	}
	ee.data.u64 = 0;
	ee.data.fd = fd;

	if(epoll_ctl(el->epfd, op, fd, &ee)==-1)	{
		printf("epoll ctl error\n");
		return -1;
	}

	fe->mask |= mask;
	if(mask&EL_EVENT_READABLE)	{
		fe->rhandler = handler;
	}
	if(mask&EL_EVENT_WRITABLE)	{
		fe->whandler = handler;
	}
	fe->data = data;
	/*
		 if (fd > eventLoop->maxfd)	{
		 eventLoop->maxfd = fd;
		 }
	 */

	return 0;
}

int event_loop_step(el_event_loop* el)
{
	int nevent;
	nevent = epoll_wait(el->epfd, el->epevents, EL_EVENT_SETSIZE, -1);
	printf("nevent=%d\n",nevent);
}

int start_event_loop(el_event_loop* el)
{
	while(!el->stopped)	{
		event_loop_step(el);
	}
}
