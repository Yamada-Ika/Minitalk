CC			:= gcc
CFLAGS		:= #-Wall -Wextra -Werror

NAME		:= Minitalk
SERVER		:= server
CLIENT		:= client
SERVER_SRCS	:= server.c
CLIENT_SRCS	:= client.c

ifdef WITH_BONUS
SERVER_SRCS		:= server_bonus.c 
CLIENT_SRCS		:= client_bonus.c
endif

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER)

$(CLIENT): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT)

bonus:
	make WITH_BONUS=1

clean:
	rm -rf $(SERVER) $(CLIENT)

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
