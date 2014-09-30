#include "Server.h"

Server::Server()
{
}

Server::Server(int port)
{
	set_port(port);
}

void Server::post_addhost()
{
	//send client the data list
	string client_list = "s:";
	for (vector<HostDetails>::iterator i = host_list.begin();
			i != host_list.end(); i++)
		client_list += i->to_string();
	int size = client_list.length() * sizeof(char);
	const char* data = client_list.c_str();
	//header += size;//TODO check if metadata needs to be sent
	for (vector<HostDetails>::iterator i = host_list.begin();
				i != host_list.end(); i++)
		send_data(i->get_socket(), (void*)data, size);
}

Server::~Server()
{
}

bool Server::command_map(vector<string> cmd)
{
	if (cmd.size() > 0 && cmd[0] == "statistics")
	{
		printf("\nclient call");
		return true;
	}
	return false;
}

void Server::receive_data(int socket)
{
	char buf[256];
	int nbytes = recv(socket, buf, sizeof(buf), 0);
	if (nbytes <= 0)
	{
		if(nbytes != 0)
			perror("recv");
		close(socket);
		FD_CLR(socket, &master);
		remove_from_hostlist(socket);
	}
	else
	{
		//server will receive statistics from the clients
	}
}
