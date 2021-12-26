/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:11 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 00:55:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <stdio.h>

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
		if (kill(pid, signal) == KILL_FAILE)
		{
			write(STDERR_FILENO, "Failed to send!\n", 16);
			exit(SEND_ERROR);
		}
		usleep(SLEEP_TIME);
		j++;
	}
}

static void	ft_send_str(pid_t pid, char *str)
{
	size_t	i;
	size_t	str_len;

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

	pid = (pid_t)strtoll(s, &end, 10);
	if (strcmp(end, "") != 0 || pid <= PID_MIN)
		exit(ARG_ERROR);
	return (pid);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	char	*str;

	if (argc != 3)
	{
		write(STDERR_FILENO, "Invalid argument!\n", 18);
		return (ARG_ERROR);
	}
	pid = ft_get_pid(argv[1]);
	if (pid == ERROR_PID)
	{
		write(STDERR_FILENO, "Invalid PID!\n", 13);
		return (ARG_ERROR);
	}
	str = argv[2];
	ft_send_str(pid, str);
}
