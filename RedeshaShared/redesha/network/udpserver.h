#ifndef REDESHA_UDPSERVER_H
#define REDESHA_UDPSERVER_H

#include <memory>
#include "packets/opcodes.h"
#include "udpstream.h"

namespace Redesha 
{
	struct char_cmp { bool operator () (const char *a,const char *b) const 
	{
		return strcmp(a,b)<0;} 
	};

	class UdpServer : virtual public UdpStream
	{
	public:
		UdpServer(unsigned short port);
		~UdpServer(void);

		virtual bool process() = 0;

	protected:
		virtual void handleReceive(ENetEvent* e);
		virtual void handleDisconnect(ENetEvent* e);
		virtual void handleWrite();
		//virtual void handleNewStream(PacketStream* stream);

		std::map<const char*, PacketStream*> packetStreams;
		std::mutex streamsMutex;
	};

};


#endif

