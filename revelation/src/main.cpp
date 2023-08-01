#include <iostream>
#include <hv/HttpServer.h>

#include "json.hpp"
#include "server.h"


int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Usage: %s port and ip\n", argv[0]);
		return -10;
	}

	int port = atoi(argv[1]);
	std::string ip = argv[2];
	MapHttpServer server(port, ip);

#ifdef OS_UNIX
	// daemon
	int ret = daemon(1, 1);
	if (ret != 0)
	{
		printf("daemon error: %d\n", ret);
		exit(-10);
	}
#endif
	server.start();

    return 0;
}