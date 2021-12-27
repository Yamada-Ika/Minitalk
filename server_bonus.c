/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 14:57:05 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "ft_receive_info.h"
#include <stdio.h>

static t_receive_info	rec;

void	ft_init_receive_info(int flag)
{
	if (flag == 0)
	{
		rec.is_len_sent = true;
		rec.bit_cnt = 0;
		rec.decimal = 0;
	}
	if (flag == 1)
	{
		rec.bit_cnt = 0;
		rec.decimal = 0;
	}
	if (flag == 2)
	{
		rec.is_len_sent = false;
		rec.bit_cnt = 0;
		rec.decimal = 0;
		rec.index = 0;
	}
}

void	ft_print_str(void)
{
	int	str_len;

	str_len = (int)strlen(rec.str);
	write(STDOUT_FILENO, rec.str, str_len + 1);
	putc('\n', stdout);
	free(rec.str);
}

bool	ft_allocate_for_str(void)
{
	int	str_len;

	str_len = rec.decimal;
	rec.str = (char *)malloc((str_len + 1) * sizeof(char));
	if (rec.str == NULL)
	{
		write(STDERR_FILENO, "Failed to memory allocate!\n", 28);
		return (false);
	}
	rec.str[str_len] = '\0';
	return (true);
}

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	rec.decimal += (sig - SIGUSR1) << rec.bit_cnt;
	rec.bit_cnt++;
	rec.client_pid = info->si_pid;
	rec.signal = sig;
	// write(STDOUT_FILENO, "called!\n", 9);
	// kill(info->si_pid, sig);
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
	while (true)
	{
		// write(STDOUT_FILENO, "paused!\n", 9);
		pause();
		// write(STDOUT_FILENO, "started!\n", 9);
		if (!rec.is_len_sent && rec.bit_cnt == sizeof(int) * BYTE)
		{
			if (!ft_allocate_for_str())
				exit(1);
			ft_init_receive_info(0);
		}
		else if (rec.is_len_sent && rec.bit_cnt == BYTE)
		{
			if (rec.decimal == EOT)
			{
				ft_print_str();
				ft_init_receive_info(2);
				// usleep(1000);
				kill(rec.client_pid, rec.signal);
				continue ;
			}
			rec.str[rec.index] = (char)(rec.decimal);
			rec.index++;
			// write(STDOUT_FILENO, &(rec.decimal), 1);
			ft_init_receive_info(1);
		}
		// write(STDOUT_FILENO, "ready?...\n", 11);
		// usleep(1000);
		kill(rec.client_pid, rec.signal);
		// write(STDOUT_FILENO, "sent!\n", 7);
	}
}

