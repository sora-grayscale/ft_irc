NAME := ircserv
NAME_DEBUG := $(NAME)_debug

CXX := c++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98
CXXFLAGS_DEBUG = $(CXXFLAGS) -g -fsanitize=address -fsanitize=leak -fsanitize=undefined #-fsanitize=integer
DEPFLAGS = -MMD -MP -MF

SRCDIR := src
SERVER_SRC =  src/Channel.cpp \
              src/CommandHandler.cpp \
              src/CommandHandler_Admin.cpp \
              src/CommandHandler_Connect.cpp \
              src/CommandHandler_Error.cpp \
              src/CommandHandler_Info.cpp \
              src/CommandHandler_Invite.cpp \
              src/CommandHandler_Join.cpp \
              src/CommandHandler_Kick.cpp \
              src/CommandHandler_Kill.cpp \
              src/CommandHandler_Links.cpp \
              src/CommandHandler_List.cpp \
              src/CommandHandler_Lusers.cpp \
              src/CommandHandler_Mode.cpp \
              src/CommandHandler_Names.cpp \
              src/CommandHandler_Nick.cpp \
              src/CommandHandler_Notice.cpp \
              src/CommandHandler_Oper.cpp \
              src/CommandHandler_Part.cpp \
              src/CommandHandler_Pass.cpp \
              src/CommandHandler_Ping.cpp \
              src/CommandHandler_Pong.cpp \
              src/CommandHandler_Privmsg.cpp \
              src/CommandHandler_Quit.cpp \
              src/CommandHandler_Time.cpp \
              src/CommandHandler_Topic.cpp \
              src/CommandHandler_Trace.cpp \
              src/CommandHandler_User.cpp \
              src/CommandHandler_Version.cpp \
              src/CommandHandler_Who.cpp \
              src/CommandHandler_Whois.cpp \
              src/CommandHandler_Whowas.cpp \
              src/CommandHandler_debug.cpp \
              src/CommandHandler_handleCommand.cpp \
              src/CommandHandler_parseMessage.cpp \
              src/Replies.cpp \
              src/Server.cpp \
              src/Server_init.cpp \
              src/Server_run.cpp \
              src/User.cpp \
              src/main.cpp

OBJDIR := obj
SERVER_OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SERVER_SRC))

OBJDIR_DEBUG := obj_debug
SERVER_OBJ_DEBUG = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR_DEBUG)/%.debug.o,$(SERVER_SRC))

INC := inc

RM := rm -rf

all: $(NAME)

run: all
	@./$(NAME) 6665 password

run_debug: debug
	@./$(NAME_DEBUG) 6665 password

run_debug_6665: debug
	@./$(NAME_DEBUG) 6665 password

run_debug_6666: debug
	@./$(NAME_DEBUG) 6666 password

run_debug_6667: debug
	@./$(NAME_DEBUG) 6667 password

run_debug_6668: debug
	@./$(NAME_DEBUG) 6668 password

run_debug_6669: debug
	@./$(NAME_DEBUG) 6669 password

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) "$(@:%.o=%.d)" -I$(INC) -c -o $@ $<
	@echo "$< =========> $(GRN) $@ $(RES)"

$(OBJDIR_DEBUG)/%.debug.o: $(SRCDIR)/%.cpp | $(OBJDIR_DEBUG)
	@$(CXX) $(CXXFLAGS_DEBUG) $(DEPFLAGS) "$(@:%.debug.o=%.d)" -I$(INC) -c -o $@ $<
	@echo "$< =========> $(GRN) $@ $(RES)"

$(NAME): $(SERVER_OBJ)
	@$(CXX) -o $@ $(SERVER_OBJ)
	@echo "$(CYN)\n=====link server=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(SERVER_OBJ)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS) $(DEPFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(CYN)==============$(RES)"

$(NAME_DEBUG): $(SERVER_OBJ_DEBUG)
	@$(CXX) $(CXXFLAGS_DEBUG) -o $(NAME_DEBUG) $(SERVER_OBJ_DEBUG)
	@echo "$(CYN)\n=====link server=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(SERVER_OBJ_DEBUG)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS_DEBUG) $(DEPFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME_DEBUG)$(RES)"
	@echo "$(CYN)==============$(RES)"

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR_DEBUG):
	@mkdir -p $@

-include $(OBJDIR)/*.d
-include $(OBJDIR_DEBUG)/*.d

debug: $(NAME_DEBUG)

clean:
	@echo "$(CYN)\n===== clean =====$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)$(OBJDIR)/*\n$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)$(OBJDIR_DEBUG)/*\n$(RES)"
	@$(RM) $(OBJDIR) $(OBJDIR_DEBUG)

fclean: clean
	@echo "$(CYN)\n===== fclean =====$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)$(NAME_DEBUG)$(RES)\n"
	@$(RM) $(NAME) $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re run server client debug run_debug run_debug_6665 run_debug_6666 run_debug_6667 run_debug_6668 run_debug_6669

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
