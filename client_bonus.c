/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 01:49:15 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

volatile sig_atomic_t	g_sig;

void	print_receive_signal(int signal)
{
	g_sig = signal;
}

int	ft_kill(pid_t pid, int signal)
{
	if (signal == SIGUSR1)
		ft_putstr_fd("SIGUSR1 sent!\n", STDOUT_FILENO);
	if (signal == SIGUSR2)
		ft_putstr_fd("SIGUSR2 sent!\n", STDOUT_FILENO);
	return (kill(pid, signal));
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
		if (bit == 0)
			signal = SIGUSR1;
		if (bit == 1)
			signal = SIGUSR2;
		if (ft_kill(pid, signal) == KILL_FAILE)
		{
			ft_putstr_fd("Failed to send!\n", STDERR_FILENO);
			exit(SEND_ERROR);
		}
		pause();
		usleep(100);
		j++;
	}
}

static void	ft_send_str(pid_t pid, char *str)
{
	size_t	str_len;
	size_t	i;

	if (str == NULL)
		return ;
	i = 0;
	str_len = strlen(str);
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
	if (strcmp(end, "") != 0 || pid <= PID_MIN)
	{
		ft_putstr_fd("Invalid PID!\n", STDERR_FILENO);
		exit(ARG_ERROR);
	}
	return (pid);
}

int	main(int argc, char *argv[])
{
	signal(SIGUSR1, print_receive_signal);
	signal(SIGUSR2, print_receive_signal);
	if (argc != 3)
	{
		ft_putstr_fd("Invalid argument!\n", STDERR_FILENO);
		return (ARG_ERROR);
	}
	ft_send_str(ft_get_pid(argv[1]), argv[2]);
}
