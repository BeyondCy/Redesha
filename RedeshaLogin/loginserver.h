#ifndef REDESHA_LOGINSERVER_H
#define REDESHA_LOGINSERVER_H

#include <thread>
#include <chrono>

#include <redesha/network/UdpStream.h>

namespace Redesha 
{

	class LoginServer
	{
	public:
		LoginServer(void);
		~LoginServer(void);

		void run();

	private:
		UdpStream* worldListener;
		UdpStream* clientListener;
	};

};


#endif