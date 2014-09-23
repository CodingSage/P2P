#ifndef P2PBASE_H
#define P2PBASE_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "global.h"
#include "HostDetails.h"

using namespace std;

class P2PBase
{
protected:
	int port, fdmax;
	fd_set master;
	int initialize();
	vector<HostDetails> host_list;
	int get_socket(string ip, string port, bool is_server);
	bool add_host(int socket_desc);
	void add_to_hostlist(string ip, string name, int port, int socket);
	void list_hosts();
	void virtual receive_data(char* buf, int nbytes) = 0;
	bool base_command_map(vector<string> cmd);
	bool virtual command_map(vector<string> cmd) = 0;
	void command_execute(string cmd);
	string get_self_ip();

public:
	P2PBase();
	P2PBase(int port);
	~P2PBase();
	void start();
	void set_port(int port);
};

#endif
