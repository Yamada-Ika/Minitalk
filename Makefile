CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=address

SERVER		:= server
CLIENT		:= client
SERVER_SRCS	:= server.c
CLIENT_SRCS	:= client.c

all: name

name: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER)

$(CLIENT): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT)

clean:
	rm -rf $(SERVER) $(CLIENT)

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
