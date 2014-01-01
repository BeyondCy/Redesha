#include "loginserver.h"

using namespace Redesha;

LoginServer::LoginServer(void)
{
	//this->clientListener = 
	LOG(INFO) << "LoginServer starting";
	this->worldManager = new WorldManager(5999);
}


LoginServer::~LoginServer(void)
{
	//delete this->clientListener;
	delete this->worldManager;
}

void LoginServer::run()
{
	while (true)
	{
//		this->clientListener->process();
		this->worldManager->process();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
