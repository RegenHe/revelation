#include <iostream>
#include <hv/hv.h>
#include <hv/HttpServer.h>

#include "json.hpp"
#include "server.h"


using namespace hv;

#define TEST_HTTPS 0

int main(int argc, char** argv) {
    MapHttpServer test(8080);
	test.start();

#ifdef OS_UNIX
	// daemon
	int ret = daemon(1, 1);
	if (ret != 0)
	{
		printf("daemon error: %d\n", ret);
		exit(-10);
	}

	while (1);
#else
	std::string str;
	while (std::getline(std::cin, str)) {
		if (str == "stop") {
			test.stop();
			break;
		}
	}
#endif

    return 0;
}