#inclulde <string>
#inclulde <vector>

class CommandHandler{
public:
    void handleCommad(const std::string &command, User &user);

private:
    void parseCommand(const std::string &commad);
    void executeCommand(const std::string &commandName, const std::vector<string> &params, User &user);

};
