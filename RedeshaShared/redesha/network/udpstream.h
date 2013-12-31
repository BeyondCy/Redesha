#ifndef REDESHA_UDPSTREAM_H
#define REDESHA_UDPSTREAM_H

#include <map>

#include <thread>
#include <mutex>

#include <exception>

#include <enet/enet.h>

#include "packetstream.h"

namespace Redesha 
{

	class UdpStream
	{
	public:
		//UdpStream() {}
		UdpStream(const char* host, unsigned short port);
		UdpStream(unsigned short port);
		virtual ~UdpStream();
	
		virtual void readLoop(); /* loop over available UDP messages */
		virtual void writeLoop();

		virtual bool process() = 0;

	protected:
		// networking
		virtual void handleConnect(ENetEvent* e);   /* new client */
		virtual void handleDisconnect(ENetEvent* e);
		virtual void handleReceive(ENetEvent* e);  /* packet received */

		virtual void handleRead(int status, ENetEvent* e) {} /* allows custom events to occur on a pulse */
		virtual void handleWrite() {} /* allows custom events to occur on a pulse */


	private:
		static unsigned int sessions;

		ENetAddress address;
		ENetHost* socket;

		std::thread readThread;
		std::thread writeThread;
		
		void initialize();
		void setSocket(unsigned short port = 0, const char* host = 0);
	};

};


#endif