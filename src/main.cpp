#include "../inc/ircserv.hpp"

// ./ircserv <port> <password>
bool isnum(const std::string& input)
{
	for (unsigned long i = 0; i < input.length(); i++)
		if (!isdigit(input[i]))
			return false;
	return true;
}

int stoi(std::string str)
{
	int  num = 0;
	if (!isnum(str))
	{
		std::cerr << "stoi erro: invalid argumet" << std::endl;
		return -1;
	}
	for (unsigned long i = 0; i < str.length(); i++)
		num = (num * 10) + (str[i] - '0');
	return num;
}

int	check_port(std::string port);
int	check_pass(std::string password);

bool	argcheck(std::string port, std::string password)
{
	if (check_port(port))
		return false;
	if (check_pass(password))
		return false;
	return true;
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "error usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	if (argcheck(argv[1], argv[2]))
		return 1;
	// 無限loop
	// server_start(port, password);
}

