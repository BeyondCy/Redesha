#ifndef REDESHA_UDPSTREAM_H
#define REDESHA_UDPSTREAM_H

#include <map>

#include <thread>
#include <mutex>
#include <atomic>  

#include <exception>

#include <enet/enet.h>

#include "packetstream.h"

namespace Redesha 
{

	class UdpStream
	{
	public:
		//UdpStream();
		UdpStream(const char* host, unsigned short port);
		UdpStream(unsigned short port);
		virtual ~UdpStream();

		void start(const char* host, unsigned short port);
		void start(unsigned short port);
	
		virtual void readLoop(); /* loop over available UDP messages */
		virtual void writeLoop();

		virtual bool process() = 0;

		void startThreads();
		void startReadThread();
		void startWriteThread();

		void stopThreads();
		void stopReadThread();
		void stopWriteThread();

	protected:
		// networking
		virtual void handleConnect(ENetEvent* e);   /* new client */
		virtual void handleDisconnect(ENetEvent* e);
		virtual void handleReceive(ENetEvent* e);  /* packet received */

		virtual void handleRead(int status, ENetEvent* e) {} /* allows custom events to occur on a pulse */
		virtual void handleWrite() {} /* allows custom events to occur on a pulse */
		
		std::thread readThread;
		std::thread writeThread;
		
		std::atomic<bool> readRun;
		std::atomic<bool> writeRun;

	private:
		static unsigned int sessions;

		ENetAddress address;
		ENetHost* socket;

		
		void initialize();
		void setSocket(unsigned short port = 0, const char* host = 0);
	};

};


#endif