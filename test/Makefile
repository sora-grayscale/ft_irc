NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
SERVER_SRC = $(SRCDIR)/main.cpp
CLIENT_SRC = $(SRCDIR)/client.cpp

OBJDIR = obj
SERVER_OBJ = $(OBJDIR)/main.o
CLIENT_OBJ = $(OBJDIR)/client.o

INC = inc

RM = rm -rf

all: server client

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -I$(INC) -MMD -MP -MF"$(@:%.o=%.d)" -c -o $@ $<
	@echo "$< =========> $(GRN) $@ $(RES)"

server: $(SERVER_OBJ)
	$(CXX) -o $@ $(SERVER_OBJ)
	@echo "$(CYN)\n=====link server=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(SERVER_OBJ)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)server$(RES)"
	@echo "$(CYN)==============$(RES)"

client: $(CLIENT_OBJ)
	$(CXX) -o $@ $(CLIENT_OBJ)
	@echo "$(CYN)\n=====link client=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(CLIENT_OBJ)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)client$(RES)"
	@echo "$(CYN)==============$(RES)"

$(OBJDIR):
	@mkdir -p $@

-include $(OBJDIR)/*.d

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	$(RM) server client

re: fclean all

.PHONY: all clean fclean re

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
