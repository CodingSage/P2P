/**
 * @vinayakk_assignment1
 * @author  Vinayak Karuppasamy <vinayakk@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "P2PBase.h"
#include "Client.h"
#include "Server.h"

#include "../include/global.h"

using namespace std;

/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */
int main(int argc, char **argv)
{
  if (argc != 3)
    printf("Invalid arguments");
  P2PBase* base;
  string mode(argv[1]);
  int port = atoi(argv[2]);
  if (mode == "s")
    base = new Server(port);
  else if (mode == "c")
    base = new Client(port);
  else
    printf("Invalid argument, select either server or client (s/c)");
  base->start();
  return 0;
}
