/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_tmp.c                                       :+:      :+:    :+:   */
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

void	sig_handler(int	signal)
{
	rec.decimal += (signal - SIGUSR1) << rec.bit_cnt;
	rec.bit_cnt++;
}

int	main(void)
{
	printf("PID : %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	rec.decimal = 0;
	rec.bit_cnt = 0;
	while (true)
	{
		pause();
		if (rec.bit_cnt == BYTE)
		{
			write(STDOUT_FILENO, (const void*)&rec.decimal, 1);
			if (rec.decimal == EOT)
				write(STDOUT_FILENO, "\n", 1);
			rec.bit_cnt = 0;
			rec.decimal = 0;
		}
	}
}
