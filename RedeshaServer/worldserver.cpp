#include "WorldServer.h"

using namespace Redesha;

WorldServer::WorldServer(const char* configFile)
	: settings(configFile)
{
	this->initLoginManager();
}


WorldServer::~WorldServer(void)
{
	if (loginManager)
		delete loginManager;
	loginManager = nullptr;
}

void WorldServer::initLoginManager()
{
	rapidxml::xml_node<>* loginNode = this->settings.first_node("loginmanager");

	char* host = loginNode->first_node("host")->value();
	unsigned short port = atoi(loginNode->first_node("port")->value());
	char* shortname = loginNode->first_node("shortname")->value();
	char* longname = loginNode->first_node("longname")->value();
	char* user = loginNode->first_node("username")->value();
	char* pass = loginNode->first_node("password")->value();

	this->loginManager = new LoginManager(host, port, shortname, longname, user, pass);
}

void WorldServer::run()
{

}