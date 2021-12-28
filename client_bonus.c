/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 19:22:26 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

volatile sig_atomic_t	g_signal;

static void	get_signal_from_server(int signal)
{
	g_signal = signal;
}

static void	ft_send_data(pid_t pid, size_t data, unsigned long size)
{
	int		signal;
	size_t	bit;
	size_t	j;

	j = 0;
	while (j < size)
	{
		bit = (data >> j) & 1;
		signal = SIGUSR1 + bit;
		if (kill(pid, signal) == KILL_FAILE)
			ft_error("Failed to send!\n", SEND_ERROR);
		pause();
		if (signal != g_signal)
			ft_error("Signal is incorrect!\n", SIG_ERROR);
		usleep(SLEEP_TIME);
		j++;
	}
}

static void	ft_send_str(pid_t pid, char *str)
{
	size_t	str_len;
	size_t	i;

	i = 0;
	str_len = ft_strlen(str);
	ft_send_data(pid, str_len, sizeof(size_t) * BYTE);
	while (i < str_len)
	{
		ft_send_data(pid, str[i], BYTE);
		i++;
	}
	ft_send_data(pid, EOT, BYTE);
}

static pid_t	ft_get_pid(char *s)
{
	pid_t	pid;
	char	*end;

	pid = (pid_t)ft_strtoll(s, &end, 10);
	if (ft_strcmp(end, "") != 0 || pid <= PID_MIN)
		ft_error("Invalid PID!\n", ARG_ERROR);
	return (pid);
}

int	main(int argc, char *argv[])
{
	signal(SIGUSR1, get_signal_from_server);
	signal(SIGUSR2, get_signal_from_server);
	if (argc != 3)
		ft_error("Invalid argument!\n", ARG_ERROR);
	ft_send_str(ft_get_pid(argv[1]), argv[2]);
}
