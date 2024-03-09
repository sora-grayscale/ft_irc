#include "CommandHandler.hpp"

void CommandHandler::printStringAsInts(const std::string &input) {
  for (std::size_t i = 0; i < input.size(); i++) {
    std::cout << static_cast<int>(input.at(i)) << " ";
  }
  std::cout << std::endl;
}

void CommandHandler::printVectorString(const std::vector<std::string> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec.at(i) << std::endl;
  }
}
