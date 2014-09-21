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
	        string cmd;     
		printf("\n> ");
		getline(cin, cmd);
		//reference : http://stackoverflow.com/questions/18941179/splitting-string-from-inputstream-with-whitespace-delimiter
		istringstream iss(cmd);
		vector<string> cmd_list;
		for(string str; iss >> str;)
		  cmd_list.push_back(str);

		//reference for string tolower : http://stackoverflow.com/questions/313970/c-stdstring-to-lower-case		      
		transform(cmd_list[0].begin(), cmd_list[0].end(), cmd_list[0].begin(), ::tolower);
						
		if(!command_map(cmd_list))
		  if(!base_command_map(cmd_list))
		     printf("\nInvalid command");		  
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

bool P2PBase::base_command_map(vector<string> commands)
{
        string cmd = commands[0];
	if (cmd == "creator")
	{
		printf("Vinayak Karuppasamy");
		printf("\nvinayakk");
		printf("\nvinayakk@buffalo.edu");
		printf("\nI have read and understood the course academic integrity policy located at http://www.cse.buffalo.edu/faculty/dimitrio/courses/cse4589_f14/index.html#integrity");	
	}
	else if (cmd == "myip")
	{
		//TODO
	  string ip = get_self_ip();
	  printf("IP address:%s", ip.c_str());
	  return true;
	}
	else if (cmd == "myport")
        {
	  printf("Port number:%d", port);
	  return true;
	}		
	return false;
}

void P2PBase::set_port(int port)
{
	this->port = port;
}

string P2PBase::get_self_ip()
{
  //reference : http://stackoverflow.com/questions/25879280/getting-my-own-ip-address-by-connecting-using-udp-socket

  addrinfo hints, *res;
  socklen_t sock_len;
  sockaddr_storage remoteaddr;
  char ip[INET_ADDRSTRLEN];
  int status;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  
  status = getaddrinfo("8.8.8.8", "5678", &hints, &res);
  if(status != 0) return "Error getting address";
  int sock_desc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(sock_desc == -1) return "Error creating socket";
  status = connect(sock_desc, res->ai_addr, res->ai_addrlen);
  if(status == -1) return "Error connecting";
  getsockname(sock_desc, (sockaddr*)&remoteaddr, &sock_len); 
  sockaddr_in* addr = (sockaddr_in*)&remoteaddr;
  inet_ntop(AF_INET, &addr->sin_addr, ip, sock_len);
  freeaddrinfo(res);
  close(sock_desc);
  return ip;
}
