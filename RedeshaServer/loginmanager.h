#pragma once

#include <redesha/network/udpclient.h>
#include <redesha/network/packets/login/loginstructs.h>

namespace Redesha 
{

	class LoginManager : UdpClient
	{
	public:
		LoginManager(const char* host, unsigned short port);
		~LoginManager(void);

		virtual bool process();

	protected:

		void handlePacket(ProtocolPacket* p);

		void handleSessionCreate(ProtocolPacket* p);
	};

}