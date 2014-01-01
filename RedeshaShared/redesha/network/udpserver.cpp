#include "udpserver.h"

using namespace Redesha;

UdpServer::UdpServer(unsigned short port, bool startThreads)
	: UdpStream(port)
{
	if (startThreads)
		this->startThreads();
}


UdpServer::~UdpServer(void)
{
	std::lock_guard<std::mutex> lock(this->streamsMutex);
	for (auto stream : this->packetStreams)
		PacketStream::destroy(stream.second);
}

void UdpServer::handleDisconnect(ENetEvent* e)
{
	char temp[25];
	sprintf(temp,"%u.%d",e->peer->address.host, e->peer->address.port);
	UdpStream::handleDisconnect(e);
	
	std::lock_guard<std::mutex> lock(this->streamsMutex);
	auto streamIter = this->packetStreams.find(temp);
	if (streamIter == this->packetStreams.end())
		return;

	PacketStream::destroy(streamIter->second);
	this->packetStreams.erase(streamIter);
}

void UdpServer::handleReceive(ENetEvent* e)
{
	char temp[25];
	sprintf(temp,"%u.%d",e->peer->address.host, e->peer->address.port);
	ProtocolPacket* pkt = new ProtocolPacket(e->packet->data, e->packet->dataLength);

	LOG(INFO) << "Received packet opcode: "<< pkt->opCode() << ", size: " << pkt->rawPacketSize() << " want: " << (unsigned short) SessionCreate;

	streamsMutex.lock();
	auto streamIter = this->packetStreams.find(temp);
	if (streamIter == this->packetStreams.end())
	{
		if (pkt->isValid() && pkt->opCode() == SessionCreate)
		{
			LOG(INFO) << "Packet valid, session start: " << e->peer->address.host << "/" << e->peer->address.port;
			PacketStream* stream = new PacketStream(e->peer);
			this->packetStreams.insert(std::pair<const char*, PacketStream*>(temp, stream));
			stream->pushOutbound(new ProtocolPacket(pkt->rawPacket(), pkt->rawPacketSize()));
			this->handleNewStream(temp, stream);
		}
		
		PacketStream::destroy(pkt);
	}
	else
	{
		streamIter->second->pushInbound(pkt);
	}
	streamsMutex.unlock();
	

	UdpStream::handleReceive(e);
}

void UdpServer::handleWrite()
{
	// todo: currently a denial of service attack could occur
	// we must put a threshold of bytes written and then decay the amount
	std::vector<PacketStream *> wants_write;
	
	streamsMutex.lock();
	for (auto stream : this->packetStreams)
		wants_write.push_back(stream.second);
	streamsMutex.unlock();

	for (auto stream : wants_write)
		stream->process();
}