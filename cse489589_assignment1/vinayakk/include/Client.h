#ifndef CLIENT_H
#define CLIENT_H

#include "P2PBase.h"

using namespace std;

class Client: public P2PBase
{
private:
	vector<HostDetails> server_list;

	bool command_map(vector<string> cmd);
	void receive_data(int socket);
	void register_server(string ip, string port);
	void connect_host(string addr, string port);
	void post_addhost();
	void update_serverlist(string buf);
	void file_transfer(char* buf);
public:
	Client();
	Client(int port);
	~Client();
};

#endif
