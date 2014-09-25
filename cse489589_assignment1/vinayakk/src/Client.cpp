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

void Client::receive_data(int socket)
{
	//TODO file transfer or host list from server
	char buf[256];
	int nbytes = recv(socket, buf, sizeof(buf), 0);
	if (nbytes <= 0)
	{
		perror("recv");
		close(socket);
		FD_CLR(socket, &master);
	}
	else
	{
	}
}

void Client::register_client(string ip, string port)
{
	int iport = atoi(port.c_str());
	if (host_list.size() > 0)
	{
		HostDetails detail = *host_list.begin();
		printf("Already registered with server: %s, %s",
				detail.get_ip().c_str(), detail.get_name().c_str());
		return;
	}
	int sock = get_socket(ip, port, false);
	FD_SET(sock, &master);
	if (sock > fdmax)
		fdmax = sock;
	//send port no.
	int sport = htonl(this->port);
	int tbytes = send(sock, &sport, sizeof(sport), 0);
	printf("bytes transferred: %d", tbytes);
	fflush(stdout);

	//TODO check this, deprecated usage
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), &addr);
	hostent *h = gethostbyaddr(&addr, sizeof(addr), AF_INET);

	add_to_hostlist(ip, string(h->h_name), iport, sock);
	list_hosts();
}
