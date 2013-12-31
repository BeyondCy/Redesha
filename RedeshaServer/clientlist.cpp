#include "clientlist.h"

using namespace Redesha;

ClientList::ClientList(void)
{
}


ClientList::~ClientList(void)
{
	for (auto clientPair : this->clientMap)
		delete clientPair.second;
}

void ClientList::add(ENetPeer* peer)
{
	Client* client = new Client(new PacketStream(peer));
	this->clientMap.insert(ClientPair(std::make_pair(peer->address.host, peer->address.port), client));
}

void ClientList::remove(ENetPeer* peer)
{
	auto it = this->clientMap.find(std::make_pair(peer->address.host, peer->address.port));
	delete it->second;
	this->clientMap.erase(it);
}

Client* ClientList::get(ENetPeer* peer)
{
	auto it = this->clientMap.find(std::make_pair(peer->address.host, peer->address.port));
	
	return (it != this->clientMap.end()) ? it->second : nullptr;
}