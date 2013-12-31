#ifndef REDESHA_CLIENT_H
#define REDESHA_CLIENT_H

#include <stdint.h>

#include <packetstream.h>

namespace Redesha {


class Client
{
public:
	Client(PacketStream* packetStream);
	~Client();

private:
	uint32_t	ip;
	uint16_t	port;
	uint32_t	connectid;
	uint32_t	charid;
	char	char_name[16];

	PacketStream* packetStream;
};



};

#endif
