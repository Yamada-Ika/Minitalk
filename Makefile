CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror

# printf
PRINTF_DIR	:= ft_printf
PRINTF		:= libftprintf.a
PRINTF		:= $(addprefix $(PRINTF_DIR)/, $(PRINTF))

# minitalk
NAME		:= Minitalk
SERVER		:= server
CLIENT		:= client
SERVER_SRCS	:= server.c
CLIENT_SRCS	:= client.c
HEADER		:= ft_minitalk.h

# bonus
ifdef WITH_BONUS
SERVER_SRCS	:= server_bonus.c server_utils_bonus.c
CLIENT_SRCS	:= client_bonus.c client_utils_bonus.c
HEADER		:= ft_minitalk_bonus.h
endif

all: $(NAME)

$(NAME): $(PRINTF) $(SERVER) $(CLIENT)

$(PRINTF): empty
	make -C $(PRINTF_DIR)

empty:

$(SERVER): $(SERVER_SRCS) $(HEADER)
	$(CC) -o $(SERVER) $(CFLAGS) $(SERVER_SRCS) $(PRINTF)

$(CLIENT): $(CLIENT_SRCS) $(HEADER)
	$(CC) -o $(CLIENT) $(CFLAGS) $(CLIENT_SRCS) $(PRINTF)

bonus:
	make WITH_BONUS=1

clean:
	rm -rf $(SERVER) $(CLIENT)

fclean: clean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re empty
