#include "client.h"


using namespace Redesha;

Client::Client(PacketStream* packetStream)
	: packetStream(packetStream)
{
	this->char_name[0] = '\0';
}


Client::~Client(void)
{
	delete packetStream;
}
