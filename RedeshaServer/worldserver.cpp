#include "WorldServer.h"

using namespace Redesha;

WorldServer::WorldServer(unsigned short port)
	: clientList(new ClientList())
{
	if (enet_initialize() != 0)
		throw std::exception("ENet failed to init.");

	this->address.host = ENET_HOST_ANY;
	this->address.port = port;

	this->server = enet_host_create (& this->address /* the address to bind the server host to */, 
								 2000      /* allow up to 2000 clients and/or outgoing connections */,
								  2      /* allow up to 2 channels to be used, 0 and 1 */,
								  0      /* assume any amount of incoming bandwidth */,
								  0      /* assume any amount of outgoing bandwidth */);

	if (this->server == NULL)
		throw std::exception("ENet failed to bind as host socket.");
}


WorldServer::~WorldServer(void)
{
	delete clientList;

	enet_host_destroy(this->server);
	enet_deinitialize();
}

void WorldServer::run()
{
//	std::this_thread::sleep_for(std::chrono::milliseconds(x));
	ENetEvent event;
    int serviceResult = 0;

	while (true)
	{
		serviceResult = 1;

		/* Keep doing host_service until no events are left */
		while (serviceResult > 0)
		{
			
			serviceResult = enet_host_service(server, &event, 50000);

			if (serviceResult > 0) 
			{
				switch(event.type) 
				{
					case ENET_EVENT_TYPE_CONNECT:
						this->handleConnect(&event);
						break;

					case ENET_EVENT_TYPE_RECEIVE:
						this->handleReceive(&event);
						break;

					case ENET_EVENT_TYPE_DISCONNECT:
						this->handleDisconnect(&event);
						break;
				}
			}
		}
	}
}

void WorldServer::handleConnect(ENetEvent* e)
{
	printf ("A new client connected from %x:%u.\n",	e->peer->address.host, e->peer->address.port);
	this->clientList->add(e->peer);
}

void WorldServer::handleDisconnect(ENetEvent* e)
{
	this->clientList->remove(e->peer);
}

void WorldServer::handleReceive(ENetEvent* e)
{
	ProtocolPacket* packet = new ProtocolPacket(e->packet->data, e->packet->dataLength);
	Client* client = this->clientList->get(e->peer);

	client->packetStream->push(packet);

    enet_packet_destroy(e->packet);
}