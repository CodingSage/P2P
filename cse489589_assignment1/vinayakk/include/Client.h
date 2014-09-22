#ifndef CLIENT_H
#define CLIENT_H

#include "P2PBase.h"

using namespace std;

class Client : public P2PBase
{
private:
        bool command_map(vector<string> cmd);	
	void receive_data(char* buf, int nbytes);
	void register_client(string ip, string port);
public:
	Client();
	Client(int port);
	~Client();
};

#endif
