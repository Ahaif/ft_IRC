NAME = ./ircserv


# Project's directories
SRCS_FOLDER = srcs
OBJECTSDIR = objects
HEADERS_FOLDER = headers

# Name of variables
FLAGS = -Wall -Wextra -Werror
CPP_STANDARD = -std=c++98

# Exercise files variable
SRC_FILES = create_socket.cpp \
poll.cpp \
request.cpp \
server.cpp \
handling_request.cpp\
request_parsing.cpp\
client.cpp\
commands.cpp\
channel.cpp\
join_command.cpp\
part_command.cpp\
kick_command.cpp\
topic.cpp\
privmsg_command.cpp\
mode.cpp\
invite.cpp\
notice.cpp\
names.cpp\
list.cpp\
bot.cpp

HEADERS_FILES = headers/server.hpp \
headers/channel.hpp\
headers/client.hpp\
headers/replay.hpp\
headers/request.hpp\

MAIN = main.cpp
# Define objects for all sources
OBJS := $(addprefix $(OBJECTSDIR)/, $(SRC_FILES:.cpp=.o))
MAIN_OBJ = $(addprefix $(OBJECTSDIR)/, $(MAIN:.cpp=.o))

# Name the compiler
CC = c++


RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
MAKE = make -C

all:  $(NAME)

# Phonebook making rules
$(NAME):  $(OBJS) $(MAIN_OBJ) $(HEADERS_FILES)
	@$(CC) $(CPP_STANDARD) $(OBJECTSDIR)/main.o $(OBJS) -o $@ -g

$(OBJECTSDIR)/%.o: $(SRCS_FOLDER)/%.cpp $(HEADERS_FILES)
	@$(MKDIR) $(dir $@)
	@$(CC) $(CPP_STANDARD) $(FLAGS) -o $@ -c $< -g

$(OBJECTSDIR)/%.o: main.cpp $(HEADERS_FILES)
	@$(CC) $(CPP_STANDARD) $(FLAGS) -o $@ -c $< -g

# Remove all objects, dependencies and executable files generated during the build
clean:
	@$(RMDIR) $(OBJECTSDIR)

fclean: clean
	@$(RM) $(NAME) $(ERRIGNORE)

re: fclean all
