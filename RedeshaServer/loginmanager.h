#pragma once

#include <redesha/network/udpclient.h>
#include <redesha/network/packets/login/loginstructs.h>

namespace Redesha 
{

	class LoginManager : virtual public UdpClient
	{
	public:
		LoginManager(const char* host, unsigned short port, 
						std::string shortname, std::string longname, 
						std::string account, std::string password);

		~LoginManager(void);

		virtual bool process();

	protected:
		void handlePacket(ProtocolPacket* p);
		void handleSessionCreate(ProtocolPacket* p);

	private:
		std::string shortname;
		std::string longname;
		std::string account;
		std::string password;
	};

}