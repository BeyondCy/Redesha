#include <stdio.h>
#include "WorldServer.h"

int main(int argc, char* argv[])
{
	try
	{
		Redesha::WorldServer server(5998);
		server.run();
	}
	catch (const std::exception &e)
	{
		fprintf(stderr, "Exception: %s", e.what());
	}

	getchar();
	return 0;
}