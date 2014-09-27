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

void Client::post_addhost()
{
}

void Client::update_serverlist(string buf)
{
	vector<HostDetails> list;
	size_t pos = buf.find(':');
	string content = buf.substr(pos + 1);
	while ((pos = content.find('-')) != string::npos)
	{
		string detail = content.substr(0, pos);
		string cdetail = content.substr(pos + 1);
		content = cdetail;
		size_t i = 0;
		vector<string> values;
		while ((i = detail.find('|')) != string::npos)
		{
			string str = detail.substr(0, i);
			detail = detail.substr(i + 1);
			values.push_back(str);
		}
		int id = atoi(values[0].c_str());
		int port = atoi(values[3].c_str());
		HostDetails host(id, values[1], values[2], port);
		list.push_back(host);
	}
	server_list = list;
	list_hosts(list);
}

void Client::file_transfer(char* buf)
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
		if (host_list.size() > 0)
		{
			HostDetails detail = *host_list.begin();
			printf("Already registered with server: %s, %s",
					detail.get_ip().c_str(), detail.get_name().c_str());
			return true;
		}
		connect_host(commands[1], commands[2]);
		return true;
	}
	else if (cmd == "connect")
	{
		if (commands.size() < 3)
		{
			printf("Invalid arguments");
			return true;
		}
		bool flag = false;
		string addr = commands[1];
		for (vector<HostDetails>::iterator i = server_list.begin();
				i != server_list.end(); i++)
		{
			if (i->get_ip() == addr || i->get_name() == addr)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			printf("Host not present in server IP list, canceling operation");
			fflush(stdout);
			return true;
		}
		connect_host(addr, commands[2]);
		return true;
	}
	else if (cmd == "terminate")
	{
		if(commands.size() > 2)
		{
			printf("Invalid arguments");
			fflush(stdout);
			return true;
		}
		int socket = atoi(commands[1].c_str());
		for (vector<HostDetails>::iterator i = host_list.begin();
				i != host_list.end(); i++)
		{
			if (i->get_id() == socket)
			{
				close(i->get_socket());
				FD_CLR(i->get_socket(), &master);
				remove_from_hostlist(i->get_socket());
				break;
			}
		}
		return true;
	}
	else if (cmd == "exit")
	{
		for (vector<HostDetails>::iterator i = host_list.begin();
				i != host_list.end(); i++)
			close(i->get_socket());
		exit(0);
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
	//TODO file transfer or host list from server; check for cases where file is large
	char buf[256];
	int nbytes = recv(socket, buf, sizeof(buf), 0);
	if (nbytes <= 0)
	{
		if (nbytes == 0)
			list_hosts();
		else
			perror("recv");
		close(socket);
		FD_CLR(socket, &master);
		remove_from_hostlist(socket);
	}
	else
	{
		char* strdata = (char*) buf;
		string data(strdata);
		if (data[0] == 's')
			update_serverlist(data);
		else
			file_transfer(buf);
	}
}

void Client::connect_host(string ip, string port)
{
	int sock = get_socket(ip, port, false), status;
	FD_SET(sock, &master);
	if (sock > fdmax)
		fdmax = sock;
	//send port no.
	int sport = htonl(this->port);
	send_data(sock, &sport, sizeof(sport));

	//TODO check this, deprecated usage
	in_addr addr;
	if ((status = inet_pton(AF_INET, ip.c_str(), &addr) <= 0))
		perror("inet_pton");
	hostent *h = gethostbyaddr(&addr, sizeof(addr), AF_INET);
	if (h == NULL)
	{
		herror("gethostbyaddr");
		return;
	}
	add_to_hostlist(ip, string(h->h_name), atoi(port.c_str()), sock);
	list_hosts();
}
