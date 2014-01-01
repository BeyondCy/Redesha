#include "packetstream.h"

using namespace Redesha;

PacketStream::PacketStream(ENetPeer* peer)
	: peer(peer)
{
}

PacketStream::~PacketStream(void)
{
	std::lock_guard<std::mutex> inlock(this->inboundMutex);
	for (auto packet : this->inboundPackets)
	{
		this->inboundPackets.pop_front();
		PacketStream::destroy(packet);
	}
	
	std::lock_guard<std::mutex> outlock(this->outboundMutex);
	for (auto packet : this->outboundPackets)
	{
		this->outboundPackets.pop_front();
		PacketStream::destroy(packet);
	}
}

void PacketStream::process(unsigned int maxPackets)
{
	while (this->hasOutbound() && maxPackets--)
		this->send(this->popOutbound());
}

void PacketStream::send(ProtocolPacket* p)
{
	PacketStream::send(this->peer, p);
}

void PacketStream::send(ENetPeer* peer, ProtocolPacket* p)
{
	ENetPacket* enetPacket = enet_packet_create(p->rawPacket(), p->rawPacketSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, p->channel(), enetPacket);
	PacketStream::destroy(p);
}

void PacketStream::pushInbound(ProtocolPacket* p)
{
	std::lock_guard<std::mutex> lock(this->inboundMutex);
	this->inboundPackets.push_back(p);
}

ProtocolPacket* PacketStream::popInbound()
{
	std::lock_guard<std::mutex> lock(this->inboundMutex);
	ProtocolPacket* p = this->inboundPackets.front();
	this->inboundPackets.pop_front();

	return p;
}

void PacketStream::pushOutbound(ProtocolPacket* p)
{
	std::lock_guard<std::mutex> lock(this->outboundMutex);
	this->outboundPackets.push_back(p);
}

ProtocolPacket* PacketStream::popOutbound()
{
	std::lock_guard<std::mutex> lock(this->outboundMutex);
	ProtocolPacket* p = this->outboundPackets.front();
	this->outboundPackets.pop_front();

	return p;
}

bool PacketStream::hasInbound()
{
	std::lock_guard<std::mutex> lock(this->inboundMutex);
	return (this->inboundPackets.size() > 0);
}

bool PacketStream::hasOutbound()
{
	std::lock_guard<std::mutex> lock(this->outboundMutex);
	unsigned long whatever = 5;
	unsigned int count = this->outboundPackets.size();
	return (count > 0);
 	return (this->outboundPackets.size() > 0);
}

void PacketStream::destroy(ProtocolPacket* p)
{
	if (p)
		delete p;
	p = nullptr;
}

void PacketStream::destroy(PacketStream* ps)
{
	if (ps)
		delete ps;
	ps = nullptr;
}