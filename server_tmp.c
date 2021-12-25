/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/25 19:31:35 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "ft_receive_info.h"
#include <stdio.h>

static t_receive_info	g_rec;

void	sig_handler(int	signal)
{
	g_rec.decimal_num += (signal - SIGUSR1) << g_rec.bit_count;
	g_rec.bit_count++;
}

int	main(void)
{
	printf("PID : %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	g_rec.decimal_num = 0;
	g_rec.bit_count = 0;
	while (true)
	{
		pause();
		if (g_rec.bit_count == BYTE)
		{
			write(STDOUT_FILENO, (const void*)&g_rec.decimal_num, 1);
			if (g_rec.decimal_num == EOT)
				write(STDOUT_FILENO, "\n", 1);
			g_rec.bit_count = 0;
			g_rec.decimal_num = 0;
		}
	}
}
