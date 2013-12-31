#include "UdpStream.h"

using namespace Redesha;


UdpStream::UdpStream(const char* host, unsigned short port)
{
	this->initialize();
	this->setSocket(port, host);
}

UdpStream::UdpStream(unsigned short port)
{
	this->initialize();
	this->setSocket(port);
}

unsigned int UdpStream::sessions = 0;

void UdpStream::initialize()
{
	if (UdpStream::sessions == 0)
		if (enet_initialize() != 0)
			throw std::exception("ENet failed to init.");

	++UdpStream::sessions;
	
	this->readThread = std::thread(&UdpStream::readLoop, this);
	this->writeThread = std::thread(&UdpStream::writeLoop, this);
}

UdpStream::~UdpStream()
{
	enet_host_destroy(this->socket);
	
	--UdpStream::sessions;
	if (UdpStream::sessions == 0)
		enet_deinitialize();

	this->readThread.join();
	this->writeThread.join();
}

void UdpStream::setSocket(unsigned short port, const char* host)
{
	this->address.port = port;
	if (!host)
	{
		this->address.host = ENET_HOST_ANY;
		this->socket = enet_host_create (& this->address, 2000, 2, 0, 0); /* 2000 clients, 2 channels */
	}
	else
	{
		enet_address_set_host (&this->address, host);
		this->socket = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);		
	}

	if (this->socket == NULL)
		throw std::exception("Failed to bind socket.");

	if (host)
	{
		ENetPeer *peer = enet_host_connect(this->socket, &this->address, 2, 0);  
		
		/* Try to connect to server within 5 seconds */
		ENetEvent event;
		if (enet_host_service (this->socket, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
			return; // good

		enet_peer_reset (peer);
		throw std::runtime_error("Failed to connect to server.");

	}
}

void UdpStream::readLoop()
{
	ENetEvent event;
    int serviceResult = 0;
	while (true)
	{
		/* Keep doing host_service until no events are left */
		while (serviceResult > 0)
		{
			
			serviceResult = enet_host_service(this->socket, &event, 10000);

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

void UdpStream::writeLoop()
{
	enet_host_flush(this->socket);
	while (true)
		this->handleWrite();
}

void UdpStream::handleConnect(ENetEvent* e)
{
	printf ("Connect from %x:%u.\n",	e->peer->address.host, e->peer->address.port);
}

void UdpStream::handleDisconnect(ENetEvent* e)
{
	printf ("Diconnect from %x:%u.\n",	e->peer->address.host, e->peer->address.port);
}

void UdpStream::handleReceive(ENetEvent* e)
{
    enet_packet_destroy(e->packet);
}
