#ifndef WorldServer_H
#define WorldServer_H

#include <exception>

#include <enet/enet.h>

#include <redesha/xmlsettings.h>

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

	protected:


		
	private:
		void initLoginManager();
		
		LoginManager* loginManager;

		XMLSettings settings;
	}; // class Worldserver

}; // namespace Redesha

#endif
