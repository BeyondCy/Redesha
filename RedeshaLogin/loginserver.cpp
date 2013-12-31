#include "loginserver.h"

using namespace Redesha;

LoginServer::LoginServer(void)
{
	this->clientListener = new UdpStream(5998);
	this->worldListener = new UdpStream(5999);
}


LoginServer::~LoginServer(void)
{
	delete this->clientListener;
	delete this->worldListener;
}

void LoginServer::run()
{
	while (true)
	{
		this->clientListener->process();
		this->worldListener->process();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
