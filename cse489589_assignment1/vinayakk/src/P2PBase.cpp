#include "P2PBase.h"

P2PBase::P2PBase()
{
	//TODO check if initial values are fine
	fdmax = 0;
	port = -1;
}

P2PBase::P2PBase(int port)
{
	set_port(port);
}

P2PBase::~P2PBase()
{
}

int P2PBase::get_socket(string ip, string port, bool is_server)
{
	const char* cport = port.c_str();
	char* cip = NULL;
	int sockfd, status;
	addrinfo hints, *res, *p;
	socklen_t sin_size;
	if (ip != "")
		cip = (char*) ip.c_str();

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (is_server)
		hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(cip, cport, &hints, &res)) != 0)
	{
		printf("Error getting address information: %s", gai_strerror(status));
		exit(0);
	}
	for (p = res; p != NULL; p = p->ai_next)
	{
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd == -1)
		{
			perror("socket");
			continue;
		}
		if (is_server)
		{
			status = bind(sockfd, p->ai_addr, p->ai_addrlen);
			if (status < 0)
			{
				perror("bind");
				close(sockfd);
				continue;
			}
		}
		break;
	}
	if (is_server)
	{
		//TODO check the max no. of connections
		listen(sockfd, MAX_PARALLEL_DOWNLOAD + 1);
	}
	else
	{
		status = connect(sockfd, p->ai_addr, p->ai_addrlen);
		if (status == -1)
			perror("connect");
	}

	freeaddrinfo(res);
	return sockfd;
}

int P2PBase::initialize()
{
	stringstream s;
	s << port;
	string strport = s.str();
	return get_socket("", strport, true);
}

void P2PBase::start()
{
	//reference : Beej's Guide to Network Programming
	fd_set read_fds;
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	int listener = initialize();
	fdmax = listener;
	FD_SET(listener, &master);
	FD_SET(0, &master); //file descriptor for std. IO
	printf("> ");
	while (true)
	{
		read_fds = master;
		fflush(stdout);
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			perror("select");
			exit(0);
		}

		for (int i = 0; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &read_fds))
			{
				if (i == listener)
					add_host(i);
				else if (i == 0)
				{
					string cmd;
					getline(cin, cmd);
					command_execute(cmd);
				}
				else
				{
					receive_data(i);
				}
			}
		}
	}
}

void P2PBase::command_execute(string cmd)
{
	//reference : http://stackoverflow.com/questions/18941179/splitting-string-from-inputstream-with-whitespace-delimiter
	if (cmd == "")
		return;
	istringstream iss(cmd);
	vector<string> cmd_list;
	for (string str; iss >> str;)
		cmd_list.push_back(str);

	//reference for string tolower : http://stackoverflow.com/questions/313970/c-stdstring-to-lower-case
	transform(cmd_list[0].begin(), cmd_list[0].end(), cmd_list[0].begin(),
			::tolower);

	if (!command_map(cmd_list))
		if (!base_command_map(cmd_list))
			printf("\nInvalid command");
	printf("\n> ");
}

bool P2PBase::add_host(int socket)
{
	if (host_list.size() > MAX_PARALLEL_DOWNLOAD + 1)
		return false;
	sockaddr_storage remote;
	char remote_ip[INET_ADDRSTRLEN];
	socklen_t addrlen = sizeof(remote);
	int new_sock = accept(socket, (sockaddr*) &remote, &addrlen);
	if (new_sock == -1)
	{
		perror("accept");
		return false;
	}
	FD_SET(new_sock, &master);
	if (new_sock > fdmax)
		fdmax = new_sock;
	char buf[256];
	int nbytes = recv(new_sock, buf, sizeof(buf), 0);
	if (nbytes == -1)
		perror("recv");
	int byteport = *((int*) buf);
	printf("bytes received : %d", nbytes);
	uint32_t nport = ntohl(byteport);
	inet_ntop(remote.ss_family, &(((sockaddr_in*)&remote)->sin_addr), remote_ip, INET_ADDRSTRLEN);

	char hostname[1024];
	char service[20];
	getnameinfo((sockaddr*) &remote, sizeof(remote), hostname, sizeof(hostname),
			service, sizeof(service), 0);
	string name(hostname);
	string ip(remote_ip);
	add_to_hostlist(ip, name, nport, new_sock);
	post_addhost();
	printf("\n> ");
	fflush(stdout);
	return true;
}

bool P2PBase::base_command_map(vector<string> commands)
{
	string cmd = commands[0];
	if (cmd == "creator")
	{
		printf("Vinayak Karuppasamy");
		printf("\nvinayakk");
		printf("\nvinayakk@buffalo.edu");
		printf("\nI have read and understood the course academic integrity policy located at http://www.cse.buffalo.edu/faculty/dimitrio/courses/cse4589_f14/index.html#integrity");
		return true;
	}
	else if (cmd == "myip")
	{
		string ip = get_self_ip();
		printf("IP address:%s", ip.c_str());
		return true;
	}
	else if (cmd == "myport")
	{
		printf("Port number:%d", port);
		return true;
	}
	else if (cmd == "list")
	{
		list_hosts();
		return true;
	}
	return false;
}

void P2PBase::set_port(int port)
{
	this->port = port;
}

string P2PBase::get_self_ip()
{
	//reference : http://stackoverflow.com/questions/25879280/getting-my-own-ip-address-by-connecting-using-udp-socket
	addrinfo hints, *res;
	socklen_t sock_len;
	sockaddr_storage remoteaddr;
	char ip[INET_ADDRSTRLEN];
	int status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	status = getaddrinfo("8.8.8.8", "5678", &hints, &res);
	if (status != 0)
		return "Error getting address";
	int sock_desc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock_desc == -1)
		return "Error creating socket";
	status = connect(sock_desc, res->ai_addr, res->ai_addrlen);
	if (status == -1)
		return "Error connecting";
	getsockname(sock_desc, (sockaddr*) &remoteaddr, &sock_len);
	sockaddr_in* addr = (sockaddr_in*) &remoteaddr;
	inet_ntop(AF_INET, &addr->sin_addr, ip, sock_len);
	freeaddrinfo(res);
	close(sock_desc);
	return ip;
}

void P2PBase::add_to_hostlist(string ip, string name, int port, int socket)
{
	int count = 0, initsize = host_list.size();
	vector<HostDetails>::iterator i;
	for (i = host_list.begin(); i != host_list.end(); ++i)
	{
		count++;
		if (i->get_id() != count)
		{
			HostDetails host(count, name, ip, port, socket);
			host_list.push_back(host);
			break;
		}
	}
	if (host_list.size() == initsize)
	{
		HostDetails host(count + 1, name, ip, port, socket);
		host_list.push_back(host);
	}
}

void P2PBase::list_hosts(vector<HostDetails> hosts)
{
	printf("\n");
	for (vector<HostDetails>::iterator i = hosts.begin(); i != hosts.end(); i++)
		printf("%-5d%-35s%-20s%-8d\n", i->get_id(), i->get_name().c_str(),
				i->get_ip().c_str(), i->get_port());
	printf("\n> ");
	fflush(stdout);
}

void P2PBase::list_hosts()
{
	list_hosts(host_list);
}

void P2PBase::remove_from_hostlist(int socket)
{
	for (vector<HostDetails>::iterator i = host_list.begin();
			i != host_list.end(); i++)
	{
		if (i->get_socket() != socket)
			continue;
		host_list.erase(i);
		break;
	}
}

int P2PBase::send_data(int socket, void* data, int size)
{
	int sent = 0, left = size;
	char* sdata = (char*) data;
	while (sent != size)
	{
		int isent = send(socket, sdata + sent, left, 0);
		if (isent == -1)
		{
			perror("send");
			return left;
		}
		left -= isent;
		sent += isent;
	}

	//TODO remove this
	if (left != 0)
	{
		printf("\nbytes left to transfer: %d", left);
		fflush(stdout);
	}
	else
	{
		printf("\nbytes transfered from socket %d: %d of %d", socket, size,
				sent);
		fflush(stdout);
	}
	return left;
}
