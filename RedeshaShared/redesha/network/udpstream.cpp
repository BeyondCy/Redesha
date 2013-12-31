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
}

UdpStream::~UdpStream()
{
	this->stopThreads();

	enet_host_destroy(this->socket);
	
	--UdpStream::sessions;
	if (UdpStream::sessions == 0)
		enet_deinitialize();

}

void UdpStream::startThreads()
{
	LOG(INFO) << "UDPStream thread loops spawned by thread id: " << std::this_thread::get_id();
	this->startReadThread();
	this->startWriteThread();
}

void UdpStream::startReadThread()
{
	this->readRun = true;
	this->readThread = std::thread(&UdpStream::readLoop, this);
}

void UdpStream::startWriteThread()
{
	this->writeRun = true;
	this->writeThread = std::thread(&UdpStream::writeLoop, this);
}

void UdpStream::stopThreads()
{
	this->stopReadThread();
	this->stopWriteThread();
}

void UdpStream::stopReadThread()
{
	this->readRun = false;
	this->readThread.join();
}

void UdpStream::stopWriteThread()
{
	this->writeRun = false;
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
		serviceResult = 1;
		/* Keep doing host_service until no events are left */
		while (serviceResult > 0)
		{
			if (!this->readRun)
				return;

			serviceResult = enet_host_service(this->socket, &event, 1000);

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

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void UdpStream::writeLoop()
{
	while (this->writeRun)
	{
		this->handleWrite();
		//enet_host_flush(this->socket);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void UdpStream::handleConnect(ENetEvent* e)
{
	LOG(INFO) << "Connection received: " << e->peer->address.host << "/" << e->peer->address.port;
}

void UdpStream::handleDisconnect(ENetEvent* e)
{
	LOG(INFO) << "Connection termination: " << e->peer->address.host << "/" << e->peer->address.port;
}

void UdpStream::handleReceive(ENetEvent* e)
{
	LOG(INFO) << "Destroying UDP packet from: " << e->peer->address.host << "/" << e->peer->address.port;
    enet_packet_destroy(e->packet);
}
