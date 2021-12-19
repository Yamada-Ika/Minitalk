/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
<<<<<<< HEAD:server_bonus.c
/*   Updated: 2021/12/08 12:21:26 by iyamada          ###   ########.fr       */
=======
/*   Updated: 2021/12/19 10:16:33 by iyamada          ###   ########.fr       */
>>>>>>> dev:server.c
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
	}
	if (flag == 1)
	{
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
	}
	if (flag == 2)
	{
		rec_info->is_str_len_sent = 0;
		rec_info->is_pid_sent = 0;
		rec_info->client_pid = 0;
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		rec_info->str_index = 0;
	}
	if (flag == 3)
	{
		rec_info->is_pid_sent = 1;
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		return ;
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

bool	ft_receive_str_malloc(char **str, int str_len)
{
	// printf("str_len : %d\n", str_len);
	*str = (char *)malloc((str_len + 1) * sizeof(char));
	if (*str == NULL)
	{
		write(STDERR_FILENO, "Failed to memory allocate!\n", 28);
		return (false);
	}
	(*str)[str_len] = '\0';
	return (true);
}

void	sig_handler(int	signal)
{
	static t_receive_info	receive;
	static char				*receive_str;
	int	tmp;

	if (receive.is_pid_sent == 1)
	{
		// usleep(100);
		kill(receive.client_pid, signal);
	}
	receive.bit_count++;
	receive.decimal_num += ((signal - SIGUSR1)
			* ft_pow(2, receive.bit_count - 1));
	// if (signal == SIGUSR1)
	// 	printf("SIGUSR1 received! %d\n", receive.bit_count);
	// if (signal == SIGUSR2)
	// 	printf("SIGUSR2 received! %d\n", receive.bit_count);
	// printf("bit : %d\n", signal - SIGUSR1);
	// printf("receive.decimal_num : %d\n", receive.decimal_num);
	if (receive.is_pid_sent == 0 && receive.bit_count == sizeof(int) * BYTE)
	{
		receive.client_pid = receive.decimal_num;
		// printf("receive.client_pid : %d\n", receive.client_pid);
		ft_init_receive_info(&receive, 3);
	}
	if (receive.is_str_len_sent == 0 && receive.bit_count == sizeof(int) * BYTE)
	{
		// printf("receive.decimal_num : %d\n", receive.decimal_num);
		// printf("receive.bit_count : %d\n", receive.bit_count);
		tmp = receive.decimal_num;
		ft_init_receive_info(&receive, 0);
		ft_receive_str_malloc(&receive_str, receive.decimal_num);
		if (receive_str == NULL)
			return ;
		// ft_init_receive_info(&receive, 0);
	}
	else if (receive.is_str_len_sent == 1 && receive.bit_count == BYTE)
	{
		if (receive.decimal_num == EOT)
		{
			ft_print_received_str(receive_str);
			ft_init_receive_info(&receive, 2);
			return ;
		}
		// printf("receive.decimal_num : %d\n", receive.decimal_num);
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
		pause();
}
