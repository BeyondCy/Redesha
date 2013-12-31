#include "udpserver.h"

using namespace Redesha;

UdpServer::UdpServer(unsigned short port)
	: UdpStream(port)
{
}


UdpServer::~UdpServer(void)
{
	std::lock_guard<std::mutex> lock(this->streamsMutex);
	for (auto stream : this->packetStreams)
		delete stream.second;
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

	delete streamIter->second;
	this->packetStreams.erase(streamIter);

}

void UdpServer::handleReceive(ENetEvent* e)
{
	char temp[25];
	sprintf(temp,"%u.%d",e->peer->address.host, e->peer->address.port);
	ProtocolPacket* pkt = new ProtocolPacket(e->packet->data, e->packet->dataLength);

	printf("Got packet");

	streamsMutex.lock();
	auto streamIter = this->packetStreams.find(temp);
	if (streamIter == this->packetStreams.end())
	{
		
		printf("New connection");
		if (pkt->isValid() && pkt->opCode() == SessionCreate)
		{
		printf("isvalid, create session");
			this->packetStreams.insert(std::pair<const char*, PacketStream*>(temp, new PacketStream(e->peer)));
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

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}