/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/25 19:35:29 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <stdio.h>

int	ft_send_data_to_pid(pid_t pid, int data, int size)
{
	int	signal;
	int	bit;
	int	j;

	j = 0;
	while (j < size)
	{
		bit = (data >> j) & 0b1;
		if (bit == 0)
			signal = SIGUSR1;
		if (bit == 1)
			signal = SIGUSR2;
		if (kill(pid, signal) == KILL_FAILE)
		{
			write(STDERR_FILENO, "Failed to send!\n", 16);
			return (SEND_FAILE);
		}
		j++;
		usleep(SLEEP_TIME);
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
	pid_t	pid;
	char	*str;

	if (argc != 3 || argv == NULL)
	{
		write(STDERR_FILENO, "Invalid argument!\n", 18);
		return (1);
	}
	pid = ft_get_pid(argv[1]);
	if (pid == ERROR_PID)
	{
		write(STDERR_FILENO, "Invalid PID!\n", 13);
		return (1);
	}
	str = argv[2];
	if (ft_send_str_to_process(pid, str) == SEND_FAILE)
		return (SEND_FAILE);
}
