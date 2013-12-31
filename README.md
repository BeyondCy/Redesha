Redesha
=======

Redesha is an open source 3D MMO project using the following permissively-licensed libraries:
<p align="center">
<table>
  <tr>
    <th>Library</th><th>Component</th><th>URL</th><th>License</th>
  </tr>
  <tr>
    <td>Ogre3D</td><td>Graphics Renderer</td><td>http://ogre3d.org</td><td>MIT</td>
</tr><tr>
	<td>Bullet</td><td>Physics</td><td>http://bulletphysics.org</td><td>zlib</td>
</tr><tr>
	<td>SFML</td><td>Sound</td><td>http://sfml-dev.org</td><td>zlib</td>
</tr><tr>
	<td>OIS</td><td>Input</td><td>http://sourceforge.net/projects/wgois/</td><td>zlib</td>
</tr><tr>
	<td>ENet</td><td>UDP Networking</td><td>http://enet.bespin.org</td><td>ENet</td>
</tr><tr>
	<td>RapidXML</td><td>Parser</td><td>http://rapidxml.sourceforge.net</td><td>Boost</td>
</tr>
</table>
</p>

Client
-------------------------

The **RedeshaClient** client process is designed to provide a seamless world without the need to load individual zones (the server-side code is still managed as zones to spread apart the network load).  It is meant to compile and run natively on any platform that the Ogre3D engine supports.  Ogre3D provides amazing framerates for high quality graphics.

<p style="text-align:center"><img src="http://i.imgur.com/FYDWXkS.png" alt="Windows, Mac OS X, Linux, iOS, Android" /></p>

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