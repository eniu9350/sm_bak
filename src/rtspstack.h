#ifndef _OSPSM_RTSPSTACK_
#define _OSPSM_RTSPSTACK_

#include "common.h"

#include "el.h"

typedef struct _rtsp_client_stack {
}rtsp_client_stack;
	
typedef struct _rtsp_server_stack {
	char* hostname;
	int port;

	int fdlisten;
	
	el_event_loop* el;
}rtsp_server_stack;









#endif

