#ifndef REDESHA_PROTOCOLPACKET_H
#define REDESHA_PROTOCOLPACKET_H

#include <stdint.h>
#include <algorithm>

namespace Redesha  {

	class ProtocolPacket
	{
	public:
		ProtocolPacket(const unsigned char* rawPacket, size_t rawSize);
		ProtocolPacket(uint16_t opcode, const unsigned char* rawStruct, size_t structSize);
		~ProtocolPacket(void);

		inline const uint16_t opCode() const { return this->opcode; }
		inline bool isValid() const { return this->valid; } // valid if passes crc

		unsigned char* rawData() const { return this->rawDataBuffer; }
		 
		unsigned char* rawPacket() const { return this->rawPacketBuffer; }
		inline size_t rawPacketSize() const { return this->rawSize; }

		inline int channel() const { return this->sendchannel; }

	protected:
		unsigned long hash_djb2(unsigned char *str);
		unsigned long hash_sdbm(unsigned char *str);

	private:
		uint16_t opcode;
		unsigned char* rawPacketBuffer;
		unsigned char* rawDataBuffer;
		size_t rawSize;

		bool valid; 
		int sendchannel;
	};

}; // namespace Redesha

#endif
