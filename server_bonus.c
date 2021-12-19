/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/19 14:50:42 by iyamada          ###   ########.fr       */
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
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		rec_info->str_index = 0;
	}
	if (flag == 3)
	{
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
	*str = (char *)malloc((str_len + 1) * sizeof(char));
	if (*str == NULL)
	{
		write(STDERR_FILENO, "Failed to memory allocate!\n", 28);
		return (false);
	}
	(*str)[str_len] = '\0';
	return (true);
}

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_receive_info	receive;
	static char				*receive_str;
	int	tmp;


	kill(info->si_pid, sig);
	receive.decimal_num += (sig - SIGUSR1) << receive.bit_count;
	receive.bit_count++;
	if (receive.is_str_len_sent == 0 && receive.bit_count == sizeof(int) * BYTE)
	{
		tmp = receive.decimal_num;
		ft_init_receive_info(&receive, 0);
		ft_receive_str_malloc(&receive_str, receive.decimal_num);
		if (receive_str == NULL)
			return ;
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

void hoge(int sig, siginfo_t *info, void *ucontext)
{
	printf("info->si_pid : %d\n", info->si_pid);
}

int	main(void)
{
	struct	sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	printf("PID : %d\n", getpid());
	// signal(SIGUSR1, sig_handler);
	// signal(SIGUSR2, sig_handler);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
