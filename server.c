/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/29 15:51:31 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "ft_receive_info.h"
#include <stdio.h>

void	ft_init_receive_info(t_receive_info *rec_info, int flag)
{
	if (flag == 0)
	{
		rec_info->is_str_len_sent = 1;
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		return ;
	}
	if (flag == 1)
	{
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		return ;
	}
	if (flag == 2)
	{
		rec_info->is_str_len_sent = 0;
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		rec_info->str_index = 0;
	}
}

void	ft_print_received_str(char *s)
{
	int	s_len;

	if (s == NULL)
		return ;
	s_len = (int)strlen(s);
	write(STDOUT_FILENO, s, s_len + 1);
	putc('\n', stdout);
	free(s);
}

void	ft_receive_str_malloc(char **str, int str_len)
{
	*str = (char *)malloc((str_len + 1) * sizeof(char));
	if (*str == NULL)
	{
		write(STDERR_FILENO, "Failed to memory allocate!\n", 28);
		return ;
	}
	(*str)[str_len] = '\0';
}

void	sig_handler(int	signal)
{
	static t_receive_info	receive;
	static char				*receive_str;

	receive.bit_count++;
	receive.decimal_num += ((signal - SIGUSR1)
			* ft_pow(2, receive.bit_count - 1));
	if (receive.is_str_len_sent == 0 && receive.bit_count == sizeof(int) * BYTE)
	{
		ft_receive_str_malloc(&receive_str, receive.decimal_num);
		if (receive_str == NULL)
			return ;
		ft_init_receive_info(&receive, 0);
	}
	else if (receive.is_str_len_sent == 1 && receive.bit_count == BYTE)
	{
		if (receive.decimal_num == EOT)
		{
			ft_print_received_str(receive_str);
			ft_init_receive_info(&receive, 2);
			return ;
		}
		receive_str[receive.str_index] = (char)(receive.decimal_num);
		receive.str_index++;
		ft_init_receive_info(&receive, 1);
	}
}

int	main(void)
{
	printf("PID : %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
	{
	}
}
