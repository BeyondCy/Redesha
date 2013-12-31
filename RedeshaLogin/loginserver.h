#ifndef REDESHA_LOGINSERVER_H
#define REDESHA_LOGINSERVER_H

#include <thread>
#include <chrono>

#include "worldmanager.h"

namespace Redesha 
{

	class LoginServer
	{
	public:
		LoginServer(void);
		~LoginServer(void);

		void run();

	private:
		WorldManager* worldManager;
		UdpServer* clientListener;
	};

};


#endif