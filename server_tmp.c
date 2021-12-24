/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/19 10:16:33 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "ft_receive_info.h"
#include <stdio.h>

static t_receive_info	g_rec;

void	ft_init_receive_info(t_receive_info *rec_info, int flag)
{
	if (flag == 0)
	{
		rec_info->is_len_sent = 1;
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
	}
	if (flag == 1)
	{
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
	}
	if (flag == 2)
	{
		rec_info->is_len_sent = 0;
		rec_info->bit_count = 0;
		rec_info->decimal_num = 0;
		rec_info->index = 0;
	}
}

void	ft_print_g_recd_str(char *s)
{
	int	s_len;

	if (s == NULL)
		return ;
	s_len = (int)strlen(s);
	write(STDOUT_FILENO, s, s_len + 1);
	putc('\n', stdout);
	free(s);
}

bool	ft_g_rec_str_malloc(char **str, int str_len)
{
	*str = (char *)malloc((str_len + 1) * sizeof(char));
	if (*str == NULL)
	{
		write(STDERR_FILENO, "Failed to memory allocate!\n", 28);
		return (false);
	}
	(*str)[str_len] = '\0';
	return (true);
}

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
	while (1)
	{
		pause();
		if (g_rec.is_len_sent == 0 && g_rec.bit_count == sizeof(int) * BYTE)
		{
			if (ft_g_rec_str_malloc(&g_rec.str, g_rec.decimal_num) == false)
				exit(1);
			ft_init_receive_info(&g_rec, 0);
		}
		else if (g_rec.is_len_sent == 1 && g_rec.bit_count == BYTE)
		{
			if (g_rec.decimal_num == EOT)
			{
				ft_print_g_recd_str(g_rec.str);
				ft_init_receive_info(&g_rec, 2);
				continue ;
			}
			g_rec.str[g_rec.index] = (char)(g_rec.decimal_num);
			g_rec.index++;
			ft_init_receive_info(&g_rec, 1);
		}
	}
}
