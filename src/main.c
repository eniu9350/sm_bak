#include "common.h"


#include "rtspstack.h"
#include "config.h"
#include "el.h"
#include "server_sm.h"
#include "net.h"

#include "cassandra.h"


sm_server smserver;

//init sm server data structure
int init_sm_server()
{
	rtsp_server_stack* stack;

	//create stack
	stack = (rtsp_server_stack*)malloc(sizeof(rtsp_server_stack));
	if((stack->el = create_event_loop())==0)	{
		printf("el creation error in sm init\n");
		return -1;
	}

	smserver.stack = stack;

	return 0;
}

int start_sm_server()
{
	rtsp_server_stack* stack = smserver.stack;
	//listen
	stack->fdlisten = net_tcp_server(smserver.stack->hostname, smserver.stack->port);

	//add event
	add_file_event(stack->el, stack->fdlisten, EL_EVENT_READABLE, sm_server_rtsp_handler, 0);

	//start el
	start_event_loop(stack->el);
}


int main()
{
	init_sm_server();

	init_config();

	start_sm_server();

	sleep(50000);

}
