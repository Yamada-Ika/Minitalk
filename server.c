/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 14:41:56 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

static t_receive_info	g_rec;

static void	ft_init_receive_info(int flag)
{
	g_rec.bit_cnt = 0;
	g_rec.decimal = 0;
	if (flag == STR_LEN_SENT)
		g_rec.is_len_sent = true;
	if (flag == STR_SENT)
	{
		g_rec.is_len_sent = false;
		g_rec.index = 0;
	}
}

static void	ft_print_str(void)
{
	ft_putstr(g_rec.str);
	ft_putchar('\n');
	free(g_rec.str);
}

static void	ft_allocate_for_str(void)
{
	int	str_len;

	str_len = g_rec.decimal;
	g_rec.str = (char *)malloc((str_len + 1) * sizeof(char));
	if (g_rec.str == NULL)
	{
		ft_putstr_fd("Failed to memory allocate!\n", STDERR_FILENO);
		exit(MEM_ERROR);
	}
	g_rec.str[str_len] = '\0';
}

static void	sig_handler(int	signal)
{
	g_rec.decimal += (signal - SIGUSR1) << g_rec.bit_cnt;
	g_rec.bit_cnt++;
}

int	main(void)
{
	ft_printf("PID : %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (true)
	{
		pause();
		if (!g_rec.is_len_sent && g_rec.bit_cnt == sizeof(size_t) * BYTE)
		{
			ft_allocate_for_str();
			ft_init_receive_info(STR_LEN_SENT);
		}
		else if (g_rec.is_len_sent && g_rec.bit_cnt == BYTE)
		{
			if (g_rec.decimal == EOT)
			{
				ft_print_str();
				ft_init_receive_info(STR_SENT);
				continue ;
			}
			g_rec.str[g_rec.index] = (char)(g_rec.decimal);
			g_rec.index++;
			ft_init_receive_info(CHAR_SENT);
		}
	}
}
