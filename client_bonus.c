/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/19 14:54:01 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <stdio.h>

void	sig_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		printf("SIGUSR1 received!\n");
	}
	if (signal == SIGUSR2)
	{
		printf("SIGUSR2 received!\n");
	}
}

int	ft_kill(pid_t pid, int signal, int num)
{
	if (signal == SIGUSR1)
	{
		printf("SIGUSR1 sent! %d\n", num + 1);
	}
	if (signal == SIGUSR2)
	{
		printf("SIGUSR2 sent! %d\n", num + 1);
	}
	return (kill(pid, signal));
}

int	ft_send_data_to_pid(pid_t pid, int data, int size)
{
	int	usr_signal;
	int	bit;
	int	j;

	j = 0;
	while (j < size)
	{
		bit = (data >> j) & 0b1;
		if (bit == 0)
			usr_signal = SIGUSR1;
		if (bit == 1)
			usr_signal = SIGUSR2;
		if (ft_kill(pid, usr_signal, j) == KILL_FAILE)
		{
			write(STDERR_FILENO, "Failed to send!\n", 16);
			return (SEND_FAILE);
		}
		usleep(1000);
		j++;
	}
	return (SEND_SUCCESS);
}

int	ft_send_str_to_process(pid_t pid, char *str)
{
	size_t	i;
	size_t	str_len;
	char	c;

	if (str == NULL)
		return (-1);
	i = 0;
	str_len = strlen(str);
	if (ft_send_data_to_pid(pid, (int)str_len, sizeof(int) * BYTE) == -1)
		return (SEND_FAILE);
	while (i < str_len)
	{
		c = str[i];
		if (ft_send_data_to_pid(pid, c, BYTE) == SEND_FAILE)
			return (SEND_FAILE);
		i++;
	}
	if (ft_send_data_to_pid(pid, EOT, BYTE) == SEND_FAILE)
		return (SEND_FAILE);
	return (SEND_SUCCESS);
}

pid_t	ft_get_pid(char *s)
{
	pid_t	pid;
	char	*end;

	pid = (pid_t)strtoll(s, &end, 10);
	if (strcmp(end, ""))
		return (ERROR_PID);
	if (pid < PID_MIN)
		return (ERROR_PID);
	return (pid);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*str;

	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	if (argc != 3 || argv == NULL)
	{
		write(STDERR_FILENO, "Invalid argument!\n", 18);
		return (1);
	}
	server_pid = ft_get_pid(argv[1]);
	if (server_pid == ERROR_PID)
	{
		write(STDERR_FILENO, "Invalid PID!\n", 13);
		return (1);
	}
	str = argv[2];
	if (ft_send_str_to_process(server_pid, str) == SEND_FAILE)
		return (SEND_FAILE);
}
