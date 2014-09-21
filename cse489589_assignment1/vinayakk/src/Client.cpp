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
      printf("\nclient call to register");
      
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
