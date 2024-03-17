#include "CommandHandler.hpp"

void CommandHandler::killUser(const std::string &nick, const std::string &comment) {
  // nickが所属しているチャンネルを探す
  // 全チャンネルイテレーターでisUserInChannelしていたらそのuserをブロードキャストし，チャンネルから退出させるremoveUser
    // findUser(nici)
    // message = comment + \n\r;
  // userを全てのベクターから外す
  // userのfdをクローズ
}

void CommandHandler::KILL() {
  // param 0 ncik
  // param 1 comment
  // kill_user
}
