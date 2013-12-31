#ifndef REDESHA_CLIENTLIST_H
#define REDESHA_CLIENTLIST_H


#include <map> /* map is faster than hash table for iterative ranges */

#include <enet/enet.h>

#include <redesha/network/packetstream.h>

#include "client.h"

namespace Redesha {

typedef std::pair<uint32_t, uint16_t> ClientAddress;
typedef std::map<ClientAddress, Client*> ClientMap;
typedef std::pair<ClientAddress, Client*> ClientPair;

class ClientList
{
public:
	ClientList(void);
	~ClientList(void);

	void add(ENetPeer* peer);
	void remove(ENetPeer* peer);

	Client* get(ENetPeer* peer);
	Client* findByName(const char* name);

private:
	ClientMap clientMap;
};


}; // namespace Redesha

#endif