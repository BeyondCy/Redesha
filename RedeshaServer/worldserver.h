#ifndef WorldServer_H
#define WorldServer_H

#include <exception>

#include <enet/enet.h>
#include <redesha/network/UdpStream.h>

#include "clientlist.h"

namespace Redesha
{

	class WorldServer : virtual public UdpStream
	{
	public:
		WorldServer(unsigned short port);
		~WorldServer(void);

		void run();

	protected:
		virtual void handleConnect(ENetEvent* e);   /* new client */
		virtual void handleDisconnect(ENetEvent* e);

		virtual void handleReceive(ENetEvent* e);  /* packet received */

	private:
		ENetAddress address;
		ENetHost* server;
		ClientList* clientList;


	}; // class Worldserver

}; // namespace Redesha

#endif
