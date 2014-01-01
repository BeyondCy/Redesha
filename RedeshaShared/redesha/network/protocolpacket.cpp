#include "protocolpacket.h"

using namespace Redesha;

ProtocolPacket::ProtocolPacket(const unsigned char* rawPacket, size_t rawSize)
    : _payloadBuffer(nullptr), _rawPacketBuffer(nullptr), _rawPacketSize(rawSize), _valid(false), _sendchannel(0)
{
    if (rawSize < 4)
        return;

    this->_opcode = (((unsigned short)rawPacket[2])<<8) | rawPacket[1];

    this->_rawPacketBuffer = new unsigned char[rawSize];
    std::copy(rawPacket, rawPacket + rawSize, this->_rawPacketBuffer);

    this->_payloadSize = -1 - 2 - 1 + rawSize - 1 - 4 - 1;
    this->_payloadBuffer = new unsigned char[this->_payloadSize];

    unsigned long hash = (this->_rawPacketBuffer[this->_rawPacketSize - 2] << 24) | (this->_rawPacketBuffer[this->_rawPacketSize - 3] << 16) | (this->_rawPacketBuffer[this->_rawPacketSize - 4] << 8) | (this->_rawPacketBuffer[this->_rawPacketSize - 5]);

    std::copy(rawPacket + 1 + 2 + 1, rawPacket + rawSize - 1 -4 - 1, this->_payloadBuffer);

    this->_valid = (hash == this->hash_djb2(this->payload(), this->payloadSize()));
}

ProtocolPacket::ProtocolPacket(uint16_t opcode, const unsigned char* rawStruct, size_t structSize)
    :  _payloadBuffer(nullptr), _rawPacketBuffer(nullptr), _opcode(opcode), _valid(true), _sendchannel(0)
{
    this->_rawPacketSize = 1 + 2 + 1 + structSize + 1 + 4 + 1;
    this->_rawPacketBuffer = new unsigned char[this->_rawPacketSize];

    unsigned int offset = 0;

    this->_rawPacketBuffer[offset++] = 0;
    this->_rawPacketBuffer[offset++] = opcode & 0xff;
    this->_rawPacketBuffer[offset++] = (opcode >> 8) & 0xff;
    _rawPacketBuffer[offset++] = 0;

    std::copy(rawStruct, rawStruct + structSize, this->_rawPacketBuffer + offset);

    offset += (unsigned int)structSize;

    this->_rawPacketBuffer[offset++] = 0;

    unsigned long hash = this->hash_djb2(rawStruct, structSize);

    this->_rawPacketBuffer[offset++] = (hash & 0xFF);
    this->_rawPacketBuffer[offset++] = (hash >> 8) & 0xFF;
    this->_rawPacketBuffer[offset++] = (hash >> 16) & 0xFF;
    this->_rawPacketBuffer[offset++] = (hash >> 24) & 0xFF;

    this->_rawPacketBuffer[offset] = 0;
}


ProtocolPacket::~ProtocolPacket(void)
{
    if (this->_rawPacketBuffer)
        delete[] this->_rawPacketBuffer;
    this->_rawPacketBuffer = nullptr;

    if (this->_payloadBuffer)
        delete[] this->_payloadBuffer;
    this->_payloadBuffer = nullptr;
}

unsigned long ProtocolPacket::hash_djb2(const unsigned char* data, size_t length)
{
    unsigned long hash = 5381;
    int c;

    while (length--)
    {
        c = *data++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

unsigned long ProtocolPacket::hash_sdbm(const unsigned char* data, size_t length)
{
    unsigned long hash = 0;
    int c;

    while (length--)
    {
        c = *data++;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
