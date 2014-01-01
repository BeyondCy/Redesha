#include "loginmanager.h"

using namespace Redesha;

LoginManager::LoginManager(const char* host, unsigned short port, 
							std::string shortname, std::string longname, 
							std::string account, std::string password)
	: UdpClient(host, port), UdpStream(host, port),
		shortname(shortname), longname(longname), 
		account(account), password(password)
{
}


LoginManager::~LoginManager(void)
{
}

bool LoginManager::process()
{
	if (!this->packetStream)
		return false;

	LOG(INFO) << "Processing stream";

	while (this->packetStream->hasInbound())
	{
		LOG(INFO) << "Incoming packet";
		ProtocolPacket* p = this->packetStream->popInbound();
		this->handlePacket(p);		
	}

	return true;
}

void LoginManager::handlePacket(ProtocolPacket* p)
{
	switch (p->opCode())
	{
	case SessionCreate:
		this->handleSessionCreate(p);
		break;

	case Login_World_RegisterReply:
		this->handleRegisterReply(p);
		break;
	}

	PacketStream::destroy(p);
}

void LoginManager::handleSessionCreate(const ProtocolPacket* p)
{
	Login_World_RegisterRequest_Struct outData;
	strcpy(outData.shortname, this->shortname.c_str());
	strcpy(outData.longname, this->longname.c_str());
	strcpy(outData.account, this->account.c_str());
	strcpy(outData.password, this->password.c_str());
	ProtocolPacket* out = 
		new ProtocolPacket(Login_World_RegisterRequest, (unsigned char*) &outData, sizeof(Login_World_RegisterRequest_Struct));
	this->packetStream->pushOutbound(out);
}

#define IN_PACKET(p, struct_type)  \
	 do { if (p->payloadSize() != sizeof(struct_type)) { \
	LOG(WARNING) << "Packet Wrong Size"; \
	return; } while(0)	

void LoginManager::handleRegisterReply(const ProtocolPacket* p)
{
	IN_PACKET(p, Login_World_RegisterReply_Struct);
	
}