#include "Server.h"


Server::Server()
{
}

Server::Server(int port)
{
	set_port(port);
}

Server::~Server()
{
}

bool Server::command_map(string cmd)
{
  return false;
}
