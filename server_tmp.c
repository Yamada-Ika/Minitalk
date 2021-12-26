/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_tmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 01:08:26 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "ft_receive_info.h"
#include <stdio.h>

static t_receive_info	g_rec;

void	sig_handler(int	signal)
{
	g_rec.decimal += (signal - SIGUSR1) << g_rec.bit_cnt;
	g_rec.bit_cnt++;
}

int	main(void)
{
	printf("PID : %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	g_rec.decimal = 0;
	g_rec.bit_cnt = 0;
	while (true)
	{
		pause();
		if (g_rec.bit_cnt == BYTE)
		{
			write(STDOUT_FILENO, (const void*)&g_rec.decimal, 1);
			if (g_rec.decimal == EOT)
				write(STDOUT_FILENO, "\n", 1);
			g_rec.bit_cnt = 0;
			g_rec.decimal = 0;
		}
	}
}
