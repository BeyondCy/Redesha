#include "loginmanager.h"

using namespace Redesha;

LoginManager::LoginManager(const char* host, unsigned short port)
	: UdpClient(host, port)
{
}


LoginManager::~LoginManager(void)
{
}

bool LoginManager::process()
{
	while (this->packetStream && this->packetStream->hasInbound())
	{
		ProtocolPacket* p = this->packetStream->popInbound();
		
	}

	return true;
}

void LoginManager::handlePacket(ProtocolPacket* p)
{
	switch (p->opCode())
	{
	case SessionCreate:
		break;
	}

	PacketStream::destroy(p);
}

void LoginManager::handleSessionCreate(ProtocolPacket* p)
{
	Login_World_RegisterRequest_Struct outData;
	//outData.
	ProtocolPacket* out = new ProtocolPacket(Login_World_RegisterRequest);
	this->packetStream->pushOutbound(out);
}