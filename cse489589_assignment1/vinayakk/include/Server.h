#ifndef SERVER_H
#define SERVER_H

#include "P2PBase.h"

using namespace std;

class Server : public P2PBase
{
private:
        bool command_map(string cmd);
public:
	Server();
	Server(int port);
	~Server();
};

#endif
