#include "net.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


int net_tcp_server(char* straddr, int port)
{
	
	struct sockaddr_in addr;
	int fdlisten;

	printf("port===%d\n", port);

	fdlisten = socket(AF_INET, SOCK_STREAM, 0);
	if(fdlisten==-1)	{
		printf("sock creation error\n");
		return -1;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(straddr && inet_aton(straddr, &addr.sin_addr)==0)	{
		close(fdlisten);
		printf("address error before binding!\n");
		return -1;
	}

	if(bind(fdlisten, (struct sockaddr*)&addr, sizeof(addr))==-1)	{
		close(fdlisten);
		printf("bind error!\n");
		perror("bind error!\n");
		return -1;
	}

	if(listen(fdlisten, 511)==-1)	{/* the magic 511 constant is from nginx */	
		close(fdlisten);
		printf("listen error!\n");
		return -1;
	}
	return fdlisten;
	//no sockopt set, see redis anet.c
}
