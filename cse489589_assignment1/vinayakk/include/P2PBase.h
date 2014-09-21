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
private:
	int port;
	vector<HostDetails> host_list;
	bool add_host(string name, string ip, int port);
	bool base_command_map(vector<string> cmd);
	bool virtual command_map(vector<string> cmd) = 0;
	string get_self_ip();
public:
	P2PBase();
	P2PBase(int port);
	~P2PBase();
	void start();
	void set_port(int port);
};

#endif
