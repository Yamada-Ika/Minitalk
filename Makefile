CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror

# printf
PRINTF_DIR	:= ft_printf
PRINTF		:= libftprintf.a
PRINTF		:= $(addprefix $(PRINTF_DIR)/, $(PRINTF))

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

$(NAME): $(PRINTF) $(SERVER) $(CLIENT)

$(PRINTF): empty
	make -C $(PRINTF_DIR)

empty:

$(SERVER): $(SERVER_SRCS)
	$(CC) -o $(SERVER) $(CFLAGS) $(SERVER_SRCS) $(PRINTF)

$(CLIENT): $(CLIENT_SRCS)
	$(CC) -o $(CLIENT) $(CFLAGS) $(CLIENT_SRCS) $(PRINTF)

bonus:
	make WITH_BONUS=1

clean:
	rm -rf $(SERVER) $(CLIENT)

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re empty
