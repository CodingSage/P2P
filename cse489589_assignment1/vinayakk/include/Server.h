#ifndef SERVER_H
#define SERVER_H

#include "P2PBase.h"

using namespace std;

class Server : public P2PBase
{
private:
        bool command_map(vector<string> cmd);
	void receive_data(char* buf, int nbytes);
public:
	Server();
	Server(int port);
	~Server();
};

#endif
