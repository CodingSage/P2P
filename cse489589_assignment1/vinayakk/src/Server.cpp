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

void Server::receive_data(int socket)
{
	char buf[256];
	int nbytes = recv(socket, buf, sizeof(buf), 0);
	if (nbytes <= 0)
	{
		perror("recv");
		close (socket);
		FD_CLR(socket, &master);
	}
	else
	{
		//It looks like the Server doesn't receive data from clients except for registering - verify
	}
}
