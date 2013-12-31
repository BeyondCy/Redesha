#include "loginserver.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
	try 
	{
		Redesha::LoginServer loginServer;
		loginServer.run();
	}
	catch (const std::exception &e)
	{
		LOG(FATAL) << "Exception: " << e.what();
	}

	return 0;
}