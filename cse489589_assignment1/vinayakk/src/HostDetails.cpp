#include "HostDetails.h"


HostDetails::HostDetails(int id, string name, string ip, int port)
{
	this->id = id;
	this->name = name;
	this->ip = ip;
	this->port = port;
}


HostDetails::~HostDetails()
{
}

string HostDetails::to_string()
{
	//TODO format according to problem statement
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