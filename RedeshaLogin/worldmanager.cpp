#include "worldmanager.h"

using namespace Redesha; 

WorldManager::WorldManager(unsigned short port)
	: UdpServer(port)
{
	LOG(INFO) << "WorldManager starting";
}


WorldManager::~WorldManager(void)
{
}

bool WorldManager::process()
{
	for (auto stream : this->packetStreams)
	{
		while (stream.second->hasInbound())
		{
			ProtocolPacket* p = stream.second->popInbound();
			this->handlePacket(stream.second, p);
		}
	}

	return true;
}

void WorldManager::handlePacket(PacketStream* stream, ProtocolPacket* p)
{
	switch (p->opCode())
	{
	case Login_World_RegisterRequest:
		this->handleRegisterRequest(stream, p);
		break;

	}

	PacketStream::destroy(p);
}


void WorldManager::handleRegisterRequest(PacketStream* stream, ProtocolPacket* p)
{
	if (p->payloadSize() != sizeof(Login_World_RegisterRequest))
	{
		printf("Payload did not match size");
	}

	printf("Register!");
}