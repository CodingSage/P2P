#include "HostDetails.h"


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
	ostringstream convert;
	convert << port;
	return id + " " + name + " " + ip + " " + convert.str();
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
	return false;// this->id < other.get_id();
}

int HostDetails::get_socket()
{
	return socket;
}

void HostDetails::set_socket(int sock)
{
	socket = sock;
}
