#include "Client.h"

Client::Client()
{
}

Client::Client(int port)
{
	set_port(port);
}

Client::~Client()
{
}

bool Client::command_map(vector<string> commands)
{
	string cmd = commands[0];
	if (cmd == "register")
	{
		if (commands.size() < 3)
		{
			printf("Invalid arguments");
			return true;
		}
		register_client(commands[1], commands[2]);
		return true;
	}
	else if (cmd == "connect")
	{
		printf("\nclient call to connect");
		return true;
	}
	else if (cmd == "list")
	{
		list_hosts();
		return true;
	}
	else if (cmd == "terminate")
	{
		printf("\nclient call");
		return true;
	}
	else if (cmd == "exit")
	{
		printf("\nclient call");
		return true;
	}
	else if (cmd == "upload")
	{
		printf("\nclient call");
		return true;
	}
	else if (cmd == "download")
	{
		printf("\nclient call");
		return true;
	}
	else if (cmd == "statistics")
	{
		printf("\nclient call");
		return true;
	}
	return false;
}

void Client::receive_data(char* buf, int nbytes)
{
	//TODO file transfer or host list from server
}

void Client::register_client(string ip, string port)
{
	if (host_list.size() > 0)
	{
		HostDetails detail = *host_list.begin();
		printf("Already registered with server: %s, %s", detail.get_ip().c_str(),
				detail.get_name().c_str());
		return;
	}
	int sock = get_socket(ip, port, false);
	FD_SET(sock, &master);
	if (sock > fdmax)
		fdmax = sock;

	//TODO check this, deprecated usage
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), &addr);
	hostent *h = gethostbyaddr(&addr, sizeof(addr), AF_INET);

	int iport = atoi(port.c_str());
	add_to_hostlist(ip, string(h->h_name), iport, sock);
	list_hosts();
	//send port no.
}
