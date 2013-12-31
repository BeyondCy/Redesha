#ifndef REDESHA_WORLDMANAGER_H
#define REDESHA_WORLDMANAGER_H

#include <redesha/network/udpserver.h>

namespace Redesha 
{

	class WorldManager : UdpServer
	{
	public:
		WorldManager(unsigned short port);
		~WorldManager();

		virtual bool process();

	protected:
		void handlePacket(PacketStream* stream, ProtocolPacket* p);

		void handleRegisterRequest(PacketStream* stream, ProtocolPacket* p);
	};

}


#endif