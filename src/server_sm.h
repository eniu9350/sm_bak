#ifndef _OSPSM_SERVER_SM_
#define _OSPSM_SERVER_SM_

#include "rtspstack.h"

typedef struct _sm_server {
	rtsp_server_stack* stack;
}sm_server;	

void sm_server_rtsp_handler(struct _el_event_loop* el, int fd, void* data, int mask);


#endif

