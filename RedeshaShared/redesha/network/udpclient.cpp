#include "udpclient.h"

using namespace Redesha;

UdpClient::UdpClient(const char* host, unsigned short port, bool startThreads)
	: UdpStream(host, port), packetStream(nullptr)
{
	if (startThreads)
		this->startThreads();
}

UdpClient::~UdpClient()
{	
	PacketStream::destroy(this->packetStream);
}

void UdpClient::handleDisconnect(ENetEvent* e)
{
	char temp[25];
	sprintf(temp,"%u.%d",e->peer->address.host, e->peer->address.port);
	UdpStream::handleDisconnect(e);
	
	PacketStream::destroy(this->packetStream);
}

void UdpClient::handleReceive(ENetEvent* e)
{
	char temp[25];
	sprintf(temp,"%u.%d",e->peer->address.host, e->peer->address.port);
	ProtocolPacket* pkt = new ProtocolPacket(e->packet->data, e->packet->dataLength);

	LOG(INFO) << "Received packet, size: " << pkt->rawPacketSize();

	if (!this->packetStream)
	{
		if (pkt->isValid() && pkt->opCode() == SessionCreate)
		{
			LOG(INFO) << "Packet valid, session start: " << e->peer->address.host << "/" << e->peer->address.port;
			this->packetStream = new PacketStream(e->peer);
		}		
		PacketStream::destroy(pkt);	
	}
	else
	{
		this->packetStream->pushInbound(pkt);
	}

	UdpStream::handleReceive(e);
}

void UdpClient::handleWrite()
{
	if (this->packetStream)
		packetStream->process();
}