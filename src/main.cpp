#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

// ./ircserv <port> <password>

int main(int argc, char **argv)
{
	int			port = 0;
	std::string	password;

	if (argc != 3)
	{
		std::cerr << "error usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
}
