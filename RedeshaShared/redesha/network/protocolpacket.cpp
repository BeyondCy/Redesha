#include "protocolpacket.h"

using namespace Redesha;

ProtocolPacket::ProtocolPacket(const unsigned char* rawPacket, size_t rawSize)
	: rawSize(rawSize), valid(false), sendchannel(0)
{
	if (rawSize < 4)
		return;

	this->opcode = (((unsigned short)rawPacket[1])<<8) | rawPacket[2];

	this->rawPacketBuffer = new unsigned char[rawSize];
	std::copy(rawPacket, rawPacket + rawSize, this->rawPacketBuffer);	
}

ProtocolPacket::ProtocolPacket(uint16_t opcode, const unsigned char* rawStruct, size_t structSize)
	: valid(true), sendchannel(0)
{
	this->rawSize = 1 + 2 + 1 + structSize + 1 + 4 + 1;
	this->rawPacketBuffer = new unsigned char[this->rawSize];	
	this->rawPacketBuffer[0] = 0;
	this->rawPacketBuffer[1] = opcode & 0xff; 
    this->rawPacketBuffer[2] = (opcode >> 8) & 0xff;
	rawPacketBuffer[3] = 0;
	std::copy(rawStruct, rawStruct + structSize, this->rawPacketBuffer + 4);
	this->rawDataBuffer[1 + 2 + 1 + structSize] = 0;
	this->rawDataBuffer[1 + 2 + 1 + structSize + 1] = 0;
}


ProtocolPacket::~ProtocolPacket(void)
{
	if (this->rawPacketBuffer)
		delete[] this->rawPacketBuffer;
	this->rawPacketBuffer = nullptr;
}

unsigned long ProtocolPacket::hash_djb2(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

unsigned long ProtocolPacket::hash_sdbm(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}