#include "HostDetails.h"

HostDetails::HostDetails(int id, string name, string ip, int port)
{
	this->id = id;
	this->name = name;
	this->ip = ip;
	this->port = port;
	this->socket = -1;
}

HostDetails::HostDetails(int id, string name, string ip, int port, int socket)
{
	this->id = id;
	this->name = name;
	this->ip = ip;
	this->port = port;
	this->socket = socket;
}

HostDetails::~HostDetails()
{
}

string HostDetails::to_string()
{
	ostringstream cport, cid;
	cport << port; cid << id;
	return cid.str() + "|" + name + "|" + ip + "|" + cport.str() + "|-";
}

int HostDetails::get_id()
{
	return id;
}

string HostDetails::get_ip()
{
	return ip;
}

string HostDetails::get_name()
{
	return name;
}

int HostDetails::get_port()
{
	return port;
}

bool HostDetails::operator<(const HostDetails &other) const
{
	return false; // this->id < other.get_id();
}

int HostDetails::get_socket()
{
	return socket;
}

void HostDetails::set_socket(int sock)
{
	socket = sock;
}

void HostDetails::set_port(int port)
{
	this->port = port;
}
