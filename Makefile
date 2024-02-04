NAME := ircserv

CXX := c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
DEPFLAGS = -MMD -MP -MF
#-pedantic-errors
SRCDIR := src
SERVER_SRC = $(SRCDIR)/main.cpp \
             $(SRCDIR)/util.cpp \
             $(SRCDIR)/User.cpp \
             $(SRCDIR)/Server.cpp

OBJDIR := obj
SERVER_OBJ = $(OBJDIR)/main.o \
             $(OBJDIR)/util.o \
             $(OBJDIR)/User.o \
             $(OBJDIR)/Server.o


CLIENT_SRC = $(SRCDIR)/client.cpp
CLIENT_OBJ = $(OBJDIR)/client.o

INC := inc

RM := rm -rf

all: server

debug: client server
# debug: CXXFLAGS += -g -fsanitize=address -fsanitize=leak #-fsanitize=integer
debug: all
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./server

run: all
	@./server

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) "$(@:%.o=%.d)" -I$(INC) -c -o $@ $<
	@echo "$< =========> $(GRN) $@ $(RES)"

server: $(SERVER_OBJ)
	@$(CXX) -o $@ $(SERVER_OBJ)
	@echo "$(CYN)\n=====link server=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(SERVER_OBJ)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS) $(DEPFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)server$(RES)"
	@echo "$(CYN)==============$(RES)"

client: $(CLIENT_OBJ)
	@$(CXX) -o $@ $(CLIENT_OBJ)
	@echo "$(CYN)\n=====link client=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(CLIENT_OBJ)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS) $(DEPFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)client$(RES)"
	@echo "$(CYN)==============$(RES)"

$(OBJDIR):
	@mkdir -p $@

-include $(OBJDIR)/*.d

clean:
	@echo "$(CYN)\n===== clean =====$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)$(OBJDIR)/*\n$(RES)"
	@$(RM) $(OBJDIR)

fclean: clean
	@echo "$(CYN)\n===== fclean =====$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)server$(RES)"
	@echo "$(YEL)delete: $(RES) $(GRN)client$(RES)\n"
	@$(RM) server client

re: fclean all

.PHONY: all clean fclean re run server client debug

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
