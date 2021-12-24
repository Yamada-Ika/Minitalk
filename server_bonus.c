/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/19 18:54:24 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "ft_receive_info.h"
#include <stdio.h>

static t_receive_info	g_rec;

void	ft_init_receive_info(int flag)
{
	if (flag == 0)
	{
		g_rec.is_len_sent = true;
		g_rec.bit_count = 0;
		g_rec.decimal_num = 0;
	}
	if (flag == 1)
	{
		g_rec.bit_count = 0;
		g_rec.decimal_num = 0;
	}
	if (flag == 2)
	{
		g_rec.is_len_sent = false;
		g_rec.bit_count = 0;
		g_rec.decimal_num = 0;
		g_rec.index = 0;
	}
}

void	ft_print_str(void)
{
	int	str_len;

	str_len = (int)strlen(g_rec.str);
	write(STDOUT_FILENO, g_rec.str, str_len + 1);
	putc('\n', stdout);
	free(g_rec.str);
}

bool	ft_allocate_for_str(void)
{
	int	str_len;

	str_len = g_rec.decimal_num;
	g_rec.str = (char *)malloc((str_len + 1) * sizeof(char));
	if (g_rec.str == NULL)
	{
		write(STDERR_FILENO, "Failed to memory allocate!\n", 28);
		return (false);
	}
	g_rec.str[str_len] = '\0';
	return (true);
}

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_rec.decimal_num += (sig - SIGUSR1) << g_rec.bit_count;
	g_rec.bit_count++;
	kill(info->si_pid, sig);
}

int	main(void)
{
	struct sigaction	act;

	printf("PID : %d\n", getpid());
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
		if (!g_rec.is_len_sent && g_rec.bit_count == sizeof(int) * BYTE)
		{
			if (!ft_allocate_for_str())
				exit(1);
			ft_init_receive_info(0);
		}
		else if (g_rec.is_len_sent && g_rec.bit_count == BYTE)
		{
			if (g_rec.decimal_num == EOT)
			{
				ft_print_str();
				ft_init_receive_info(2);
				continue ;
			}
			g_rec.str[g_rec.index] = (char)(g_rec.decimal_num);
			g_rec.index++;
			ft_init_receive_info(1);
		}
	}
}

