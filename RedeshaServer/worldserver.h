#ifndef WorldServer_H
#define WorldServer_H

#include <exception>

#include <enet/enet.h>

#include "loginmanager.h"
#include "clientlist.h"

namespace Redesha
{

	class WorldServer
	{
	public:
		WorldServer(const char* configFile);
		~WorldServer(void);

		void run();
		
	private:
		LoginManager* loginManager;
		//ClientList* clientList;


	}; // class Worldserver

}; // namespace Redesha

#endif
