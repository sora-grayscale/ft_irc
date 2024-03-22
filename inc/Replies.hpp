#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Channel.hpp"
#include <sstream>
#include <string>

class Replies {
public:
  // 001
  static const std::string RPL_WELCOME(const std::string &nick,
                                       const std::string &user,
                                       const std::string &host);
  // 002
  static const std::string RPL_YOURHOST(const std::string &servername,
                                        const std::string &ver);
  // 003
  static const std::string RPL_CREATED(const std::string &date);
  // 004
  static const std::string RPL_MYINFO(const std::string &servername,
                                      const std::string &version,
                                      const std::string &availUserMode,
                                      const std::string &availChannelMode);
  // 221
  static const std::string RPL_UMODEIS(const std::string &userModeString);
  // 251
  static const std::string
  RPL_LUSERCLIENT(const int &users, const int &services, const int &servers);
  // 252
  static const std::string RPL_LUSEROP(const int &operators);
  // 253
  static const std::string RPL_LUSERUNKNOWN(const int &unknown);
  // 254
  static const std::string RPL_LUSERCHANNELS(const int &channels);
  // 255
  static const std::string RPL_LUSERME(const int &clients, const int &servers);
  // 256
  static const std::string RPL_ADMINME(const std::string &serverName);
  // 257
  static const std::string RPL_ADMINLOC1(const std::string &adminLocation);
  // 258
  static const std::string RPL_ADMINLOC2(const std::string &adminAffiliation);
  // 259
  static const std::string RPL_ADMINEMAIL(const std::string &adminMail);
  // 311
  static const std::string RPL_WHOISUSER(const std::string &nick,
                                         const std::string &user,
                                         const std::string &host,
                                         const std::string &realname);
  // 312
  static const std::string RPL_WHOISSERVER(const std::string &nick,
                                           const std::string &server,
                                           const std::string &serverinfo);
  // 313
  static const std::string RPL_WHOISOPERATOR(const std::string &nick);
  // 314
  static const std::string RPL_WHOWASUSER(const std::string &nick,
                                          const std::string &user,
                                          const std::string &host,
                                          const std::string &realname);
  // 315
  static const std::string RPL_ENDOFWHO(const std::string &name);
  // 318
  static const std::string RPL_ENDOFWHOIS(const std::string nick);
  // 319
  static const std::string RPL_WHOISCHANNELS(const std::string nick,
                                             const std::string channel);
  // 321
  static const std::string RPL_LISTSTART();
  // 322
  static const std::string RPL_LIST(const std::string &channel,
                                    const std::size_t &visible,
                                    const std::string &topic);
  // 323
  static const std::string RPL_LISTEND();
  // 324
  static const std::string RPL_CHANNELMODEIS(const std::string &channelName,
                                             const std::string &mode);
  // 324
  static const std::string RPL_CHANNELMODEIS(const std::string &channelName,
                                             const std::string &mode,
                                             const std::size_t &modeParams);
  // 325
  static const std::string RPL_UNIQOPIS(const std::string &channelName,
                                        const std::string &nick);
  // 329
  static const std::string RPL_CREATIONTIME(const std::string &channelName,
                                            std::time_t creationTime);
  // 331
  static const std::string RPL_NOTOPIC(const std::string &channel);
  // 332
  static const std::string RPL_TOPIC(const std::string &channelName,
                                     const std::string &topic);
  // 333
  static const std::string RPL_TOPICWHOTIME(const std::string &channelName,
                                            const std::string &nick,
                                            const std::time_t &setat);
  // 341
  static const std::string RPL_INVITING(const std::string &channel,
                                        const std::string &nick);
  // 346
  static const std::string RPL_INVITELIST(const std::string &channelName,
                                          const std::string &mask);
  // 347
  static const std::string RPL_ENDOFINVITELIST(const std::string &channelName);
  // 348
  static const std::string RPL_EXCEPTLIST(const std::string &channelName,
                                          const std::string &mask);
  // 349
  static const std::string RPL_ENDOFEXCEPTLIST(const std::string &channelName);
  // 351
  static const std::string RPL_VERSION(const std::string &version,
                                       const std::string &debuglevel,
                                       const std::string &server,
                                       const std::string &comments);
  // 352
  static const std::string
  RPL_WHOREPLY(const std::string &channel, const std::string &user,
               const std::string &host, const std::string &server,
               const std::string &nick, const std::string &realname);
  // 353
  static const std::string RPL_NAMREPLY(const Channel &channel,
                                        const User &user);
  // 366
  static const std::string RPL_ENDOFNAMES(const std::string &channelName);
  // 367
  static const std::string RPL_BANLIST(const std::string &channelName,
                                       const std::string &mask);
  // 368
  static const std::string RPL_ENDOFBANLIST(const std::string &channelName);
  // 369
  static const std::string RPL_ENDOFWHOWAS(const std::string &nick);
  // 371
  static const std::string RPL_INFO(const std::string detail,
                                    const std::string &str);
  // 372
  static const std::string RPL_MOTD();
  // 374
  static const std::string RPL_ENDOFINFO();
  // 375
  static const std::string RPL_MOTDSTART();
  // 376
  static const std::string RPL_ENDOFMOTD();
  // 381
  static const std::string RPL_YOUREOPER();
  // 391
  static const std::string RPL_TIME(const std::string &serverName,
                                    const std::string &time);
  // 401
  static const std::string ERR_NOSUCHNICK(const std::string &nickName);
  // 402
  static const std::string ERR_NOSUCHSERVER(const std::string &serverName);
  // 403
  static const std::string ERR_NOSUCHCHANNEL(const std::string &channelName);
  // 404
  static const std::string ERR_CANNOTSENDTOCHAN(const std::string &channelName);
  // 405
  static const std::string ERR_TOOMANYCHANNELS(const std::string &channelName);
  // 406
  static const std::string ERR_WASNOSUCHNICK(const std::string &nickName);
  // 411
  static const std::string ERR_NORECIPIENT(const std::string &command);
  // 412
  static const std::string ERR_NOTEXTTOSEND();
  // 421
  static const std::string ERR_UNKNOWNCOMMAND(const std::string &command);
  // 422
  static const std::string ERR_NOMOTD();
  // 431
  static const std::string ERR_NONICKNAMEGIVEN();
  // 432
  static const std::string ERR_ERRONEUSNICKNAME(const std::string &nick);
  // 433
  static const std::string ERR_NICKNAMEINUSE(const std::string &nick);
  // 436
  static const std::string ERR_NICKCOLLISION(const std::string &nick,
                                             const std::string &user,
                                             const std::string &host);
  // 437
  static const std::string ERR_UNAVAILRESOURCE(const std::string &str);
  // 441
  static const std::string ERR_USERNOTINCHANNEL(const std::string &nick,
                                                const std::string &channel);
  // 442
  static const std::string ERR_NOTONCHANNEL(const std::string &channel);
  // 443
  static const std::string ERR_USERONCHANNEL(const std::string &nick,
                                             const std::string &channel);
  // 451
  static const std::string ERR_NOTREGISTERED();
  // 461
  static const std::string ERR_NEEDMOREPARAMS(const std::string &command);
  // 462
  static const std::string ERR_ALREADYREGISTRED();
  // 464
  static const std::string ERR_PASSWDMISMATCH();
  // 467
  static const std::string ERR_KEYSET(const std::string &channelName);
  // 471
  static const std::string ERR_CHANNELISFULL(const std::string &channelName);
  // 472
  static const std::string ERR_UNKNOWNMODE(const char c,
                                           const std::string &channelName);
  // 473
  static const std::string ERR_INVITEONLYCHAN(const std::string &channelName);
  // 474
  static const std::string ERR_BANNEDFROMCHAN(const std::string &channelName);
  // 475
  static const std::string ERR_BADCHANNELKEY(const std::string &channelName);
  // 476
  static const std::string ERR_BADCHANMASK(const std::string &channelName);
  // 477
  static const std::string ERR_NOCHANMODES(const std::string &channelName);
  // 481
  static const std::string ERR_NOPRIVILEGES();
  // 482
  static const std::string ERR_CHANOPRIVSNEEDED(const std::string &channel);
  // 484
  static const std::string ERR_RESTRICTED();
  // 491
  static const std::string ERR_NOOPERHOST();
  // 501
  static const std::string ERR_UMODEUNKNOWNFLAG();
  // 502
  static const std::string ERR_USERSDONTMATCH();
};

#endif // REPLIES
