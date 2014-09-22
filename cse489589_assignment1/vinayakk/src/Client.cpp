#include "Client.h"


Client::Client()
{
}

Client::Client(int port)
{
	set_port(port);
}

Client::~Client()
{
}

bool Client::command_map(vector<string> commands)
{
  string cmd = commands[0];
  if(cmd == "register")
    {
      if(commands.size() < 3)
	{
	  printf("Invalid arguments");      
	  return true;
	}
      register_client(commands[1], commands[2]);
      return true;
    }
  else if(cmd == "connect")
    {
      printf("\nclient call to connect");
      return true;
    }
  else if(cmd == "list")
    {
      printf("\nclient call");
      return true;
    }
  else if(cmd == "terminate")
    {
      printf("\nclient call");
      return true;
    }
  else if(cmd == "exit")
    {
      printf("\nclient call");
      return true;
    }
  else if(cmd == "upload")
    {
      printf("\nclient call");
      return true;
    }
  else if(cmd == "download")
    {
      printf("\nclient call");
      return true;
    }
  else if(cmd == "statistics")
    {
      printf("\nclient call");
      return true;
    }
  return false;
}

void Client::receive_data(char* buf, int nbytes)
{
  //TODO file transfer or host list from server
}

void Client::register_client(string ip, string port)
{
  int sock = get_socket(ip, port, false);
  add_host(sock);
}
