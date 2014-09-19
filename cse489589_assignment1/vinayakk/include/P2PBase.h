#ifndef P2PBASE_H
#define P2PBASE_H

#include <sys/socket.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "global.h"
#include "HostDetails.h"

using namespace std;

class P2PBase
{
private:
	int port;
	vector<HostDetails> host_list;
	bool add_host(string name, string ip, int port);
	bool command_map(string cmd);
	string get_self_ip();
public:
	P2PBase();
	P2PBase(int port);
	~P2PBase();
	void start();
	void set_port(int port);
};

#endif
