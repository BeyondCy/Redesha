Redesha
=======

Redesha is an open source 3D MMO project using the following open source libraries:

* Ogre3D Graphics Engine
* Bullet Physics Library
* OpenAL Sound Library
* OIS Input Library
* ENet UDP Network Library
* RapidXML

Client
-------------------------

The **RedeshaClient** client process is designed to provide a seamless world without the need to load individual zones (the server-side code is still managed as zones to spread apart the network load).  It is meant to compile and run natively on any platform that the Ogre3D engine supports, including but not limited to:

* Windows
* Linux
* Mac
* Android
* iOS

Server
-------------------------

The server is broken into 3 separate processes, each with their own threads.

**RedeshaLogin**
The RedeshaLogin server securely connects clients, authenticated by username and passwords, to a list of RedeshaWorld servers.

* ClientManager - read/write IO threads for connecting RedeshaClient clients
* WorldManager - read/write IO threads for registering RedeshaWorld servers
* Main Thread - Processes packets

**RedeshaWorld**
The RedeshaWorld server registers with the RedeshaLoginServer, accepts RedeshaClient clients connecting from it, and spawns RedeshaZone processes as needed

* ClientManager - read/write IO threads for connecting RedeshaClient clients
* LoginManager - read/write IO threads for registering with RedeshaLogin server
* ZoneManager - read/write IO threads for registering RedeshaZone servers
* Main Thread - Processes packets

**RedeshaZone**
The RedeshaZone servers are spawned by RedeshaWorld servers and handle most client actions

* ClientManager - read/write IO threads for connecting RedeshaClient clients
* WorldManager - read/write IO threads for communication wtih RedeshaWorld server
* Main Thread - Processes packets


Shared
-------------------------

A static shared library is linked to by all servers and the client.  It contains common utilities, 3rd party libraries, and gamewide constants such as opcodes and packet structures.