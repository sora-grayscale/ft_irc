#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

// ./ircserv <port> <password>
bool isnum(const std::string& input)
{
	for (unsigned long i = 0; i < input.length(); i++)
		if (!isdigit(input[i]))
			return false;
	return true;
}

int	check_port(std::string port);
int	check_pass(std::string password);

int	argcheck(std::string port, std::string password)
{
	if (check_port(port))
		return 1;
	if (check_pass(password))
		return 1;
	return 0;
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "error usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	argcheck(argv[1], argv[2]);
}

