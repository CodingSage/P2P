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

bool Server::command_map(vector<string> cmd)
{
  return false;
}

void Server::receive_data(char* buf, int nbytes)
{
  //TODO update host list
}
