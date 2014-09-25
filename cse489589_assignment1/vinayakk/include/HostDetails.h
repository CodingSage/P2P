#ifndef HOSTDETAILS_H
#define HOSTDETAILS_H

#include <string>
#include <sstream>

using namespace std;

class HostDetails
{
private:
	int id;
	string name;
	string ip;
	int port;
	int socket;

public:
	HostDetails(int id, string name, string ip, int port, int socket);
	~HostDetails();
	//reference for vector sort: http://stackoverflow.com/questions/9706517/sort-a-vector-of-objects-by-an-objects-attribute
	bool operator <(const HostDetails &host) const;
	string to_string();
	int get_id();
	string get_name();
	string get_ip();
	int get_port();
	int get_socket();
	void set_socket(int sock);
	void set_port(int port);
};

#endif
