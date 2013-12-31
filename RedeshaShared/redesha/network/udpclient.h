#ifndef REDESHA_UDPSERVER_H
#define REDESHA_UDPSERVER_H

#include <memory>
#include "packets/opcodes.h"
#include "udpstream.h"

namespace Redesha 
{

	class UdpClient : virtual public UdpStream
	{
	public:
		UdpClient(const char* host, unsigned short port);
		~UdpClient(void);

		virtual bool process() = 0;

	protected:
		virtual void handleReceive(ENetEvent* e);
		virtual void handleDisconnect(ENetEvent* e);
		virtual void handleWrite();

		PacketStream* packetStream;
	};

};


#endif

