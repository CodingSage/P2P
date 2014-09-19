#include "P2PBase.h"


P2PBase::P2PBase()
{
}

P2PBase::P2PBase(int port)
{
	set_port(port);
}


P2PBase::~P2PBase()
{
}

void P2PBase::start()
{
	while (true)
	{
	        string cmd, cmd_str;	       
		printf("\n> ");
		getline(cin, cmd);
		//reference for string tolower : http://stackoverflow.com/questions/313970/c-stdstring-to-lower-case
		transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
		command_map(cmd);
	}	
}

bool P2PBase::add_host(string name, string ip, int port)
{
	int count = 0;
	vector<HostDetails>::iterator i;
	//TODO add host limit check here
	if (host_list.size() == MAX_PARALLEL_DOWNLOAD + 1)
		return false;
	for (i = host_list.begin(); i != host_list.end(); ++i)
	{
		count++;
		if (i->get_id() != count)
		{
			HostDetails host(count, name, ip, port);
			host_list.push_back(host);
			//TODO sort host list
		}
	}
	return true;
}

bool P2PBase::command_map(string cmd)
{
	if (cmd == "creator")
	{
		printf("\nVinayak Karuppasamy");
		printf("\nvinayakk");
		printf("\nvinayakk@buffalo.edu");
		printf("\nI have read and understood the course academic integrity policy located at http://www.cse.buffalo.edu/faculty/dimitrio/courses/cse4589_f14/index.html#integrity");	
	}
	else if (cmd == "myip")
	{
		//TODO
	  string ip = get_self_ip();
	  printf("IP address:%s", ip.c_str());
	}
	else if (cmd == "myport")
		printf("Port number:%d", port);
	return false;
}

void P2PBase::set_port(int port)
{
	this->port = port;
}

string P2PBase::get_self_ip()
{
  	  const int server_port = 5432;
	  const char* google_dns = "8.8.8.8";
	  hostent server_addr = gethostbyname(google_dns);
	  int s = socket(PF_INET, SOCK_DGRAM, 0);
	  sockaddr_in addr;
	  bzero((char*)&addr, sizeof(addr));
	  addr.sin_family = AF_INET;
	  bcopy(server_addr->h_addr, (char*)&addr.sin_addr, addr->h_length);
	  addr->sin_port = htons(server_port);
	  connect(s, (sockaddr_in*)&addr, sizeof(addr));
	  return addr.sin_addr.s_addr;
}