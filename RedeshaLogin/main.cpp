#include "loginserver.h"

int main(int argc, char* argv[])
{
	try 
	{
		Redesha::LoginServer loginServer;
		loginServer.run();
	}
}