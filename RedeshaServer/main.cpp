#include "WorldServer.h"

#define _ELPP_THREAD_SAFE
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
	try
	{
		Redesha::WorldServer server("redesha_world_config.xml");
		server.run();
	}
	catch (const std::exception &e)
	{
		LOG(FATAL) << "Exception: " << e.what();
	}

	return 0;
}