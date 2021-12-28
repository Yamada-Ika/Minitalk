CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror

# libft
LIBFT_DIR	:= libft
LIBFT_A		:= libft.a
LIBFT_A		:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_A))

# ft_printf mandatory
NAME 		:= libftprintf.a
HEADER		:= ft_printf.h
SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:%.c=out/%.o)

all: dir $(NAME)

dir:
	mkdir -p out

$(NAME): $(LIBFT_A) $(OBJS) $(HEADER)
	cp $(LIBFT_A) $(NAME)
	ar rc $(NAME) $(OBJS)

$(LIBFT_A): empty
	make -C $(LIBFT_DIR)

empty:

out/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf out/*.o out
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft empty dir
