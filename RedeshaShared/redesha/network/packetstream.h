#ifndef REDESHA_PACKETSTREAM_H
#define REDESHA_PACKETSTREAM_H

#include <thread>
#include <mutex>
#include <queue>
#include <deque>
#include <enet/enet.h>

#include "protocolpacket.h"

namespace Redesha {


	class PacketStream
	{
	public:
		PacketStream(ENetPeer* peer);
		~PacketStream(void);

		void process(unsigned int maxPackets = 10);
		void send(ProtocolPacket* p); // blocks current thread, prefer pushOutbound(p)

		void pushInbound(ProtocolPacket* p);
		ProtocolPacket* popInbound();
		void pushOutbound(ProtocolPacket* p);
		ProtocolPacket* popOutbound();

		bool hasOutbound();
		bool hasInbound();

		static void destroy(ProtocolPacket* p);

	private:
		ENetPeer* peer;

		std::deque<ProtocolPacket*> inboundPackets;
		std::deque<ProtocolPacket*> outboundPackets;

		std::mutex inboundMutex;
		std::mutex outboundMutex;
	};

}; // namespace Redesha

#endif