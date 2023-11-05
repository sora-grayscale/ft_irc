#include <iostream>
#include <vector>
#define fast std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
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
