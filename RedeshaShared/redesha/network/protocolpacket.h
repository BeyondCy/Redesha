#ifndef REDESHA_PROTOCOLPACKET_H
#define REDESHA_PROTOCOLPACKET_H

#include <stdint.h>
#include <algorithm>

namespace Redesha  {

    class ProtocolPacket
    {
    public:
        ProtocolPacket(const unsigned char* rawPacket, size_t _rawPacketSize);
        ProtocolPacket(uint16_t _opcode, const unsigned char* rawStruct, size_t structSize);
        ~ProtocolPacket(void);

        inline const uint16_t opCode() const { return this->_opcode; }
        inline bool isValid() const { return this->_valid; } // valid if passes crc

        unsigned char* payload() const { return this->_payloadBuffer; }
        inline size_t payloadSize() const { return this->_payloadSize; }

        unsigned char* rawPacket() const { return this->_rawPacketBuffer; }
        inline size_t rawPacketSize() const { return this->_rawPacketSize; }

        inline int channel() const { return this->_sendchannel; }

    protected:
        unsigned long hash_djb2(const unsigned char* data, size_t length);
        unsigned long hash_sdbm(const unsigned char* data, size_t length);

    private:
        uint16_t _opcode;
        unsigned char* _rawPacketBuffer;
        unsigned char* _payloadBuffer;
        size_t _rawPacketSize;
        size_t _payloadSize;

        bool _valid;
        int _sendchannel;
    };

} // namespace Redesha

#endif
