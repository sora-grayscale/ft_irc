#include "../inc/LibUtils.hpp"

bool LibUtil::isnum(const std::string &input) {
  for (unsigned long i = 0; i < input.length(); i++)
    if (!isdigit(input[i]))
      return false;
  return true;
}

int LibUtil::stoi(std::string str) {
  int num = 0;
  if (!isnum(str)) {
    std::cerr << "stoi erro: invalid argumet" << std::endl;
    return -1;
  }
  for (unsigned long i = 0; i < str.length(); i++)
    num = (num * 10) + (str[i] - '0');
  return num;
}
