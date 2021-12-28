/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 19:22:08 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

volatile sig_atomic_t	g_signal;

static void	ft_print_str(t_receive_info *rec)
{
	ft_putstr(rec->str);
	ft_putchar('\n');
	free(rec->str);
	ft_init_receive_info(rec, STR_SENT);
}

static void	ft_allocate_for_str(t_receive_info *rec)
{
	size_t	str_len;

	str_len = rec->decimal;
	rec->str = (char *)malloc((str_len + 1) * sizeof(char));
	if (rec->str == NULL)
		ft_error("Failed to memory allocate!", MEM_ERROR);
	rec->str[str_len] = '\0';
	ft_init_receive_info(rec, STR_LEN_SENT);
}

static void	ft_receive_signal(int sig, siginfo_t *info, void *ucontext)
{
	g_signal = sig;
	ucontext = NULL;
	usleep(SLEEP_TIME);
	if (kill(info->si_pid, sig) == KILL_FAILE)
		ft_error("Failed to send!", STDERR_FILENO);
}

static void	ft_set_signal_handler(struct sigaction *act,
	void (*handler)(int sig, siginfo_t *info, void *ucontext))
{
	sigemptyset(&(act->sa_mask));
	act->sa_sigaction = handler;
	act->sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, act, NULL);
	sigaction(SIGUSR2, act, NULL);
}

int	main(void)
{
	struct sigaction		act;
	static t_receive_info	rec;

	ft_printf("PID : %d\n", getpid());
	ft_set_signal_handler(&act, ft_receive_signal);
	while (true)
	{
		pause();
		rec.decimal += (g_signal - SIGUSR1) << rec.bit_cnt;
		rec.bit_cnt++;
		if (!rec.is_len_sent && rec.bit_cnt == sizeof(size_t) * BYTE)
			ft_allocate_for_str(&rec);
		else if (rec.is_len_sent && rec.bit_cnt == BYTE)
		{
			if (rec.decimal == EOT)
			{
				ft_print_str(&rec);
				continue ;
			}
			rec.str[rec.index] = rec.decimal;
			rec.index++;
			ft_init_receive_info(&rec, CHAR_SENT);
		}
	}
}
