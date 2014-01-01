#ifndef REDESHA_WORLDMANAGER_H
#define REDESHA_WORLDMANAGER_H

#include <redesha/network/udpserver.h>
#include <redesha/network/packets/login/loginstructs.h>

namespace Redesha 
{

	class WorldManager : UdpServer
	{
	public:
		WorldManager(unsigned short port);
		~WorldManager();

		virtual bool process();

	protected:
		virtual void handlePacket(PacketStream* stream, ProtocolPacket* p);
		virtual void handleNewStream(const char* name, PacketStream* stream);

		virtual void handleRegisterRequest(PacketStream* stream, ProtocolPacket* p);
	};

}


#endif