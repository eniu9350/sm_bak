#include "config.h"

#include "server_sm.h"

extern sm_server smserver;

int init_smserver_config()
{
	smserver.stack->hostname = "127.0.0.1";
	smserver.stack->port = 554;
}

int init_config()
{
	init_smserver_config();
}
