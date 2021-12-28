/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 16:30:05 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

volatile sig_atomic_t	g_sig;

static void	ft_init_receive_info(t_receive_info *rec, int flag)
{
	rec->bit_cnt = 0;
	rec->decimal = 0;
	if (flag == STR_LEN_SENT)
		rec->is_len_sent = true;
	if (flag == STR_SENT)
	{
		rec->is_len_sent = false;
		rec->index = 0;
	}
}

static void	ft_print_str(t_receive_info *rec)
{
	ft_putstr(rec->str);
	ft_putchar('\n');
	free(rec->str);
	ft_init_receive_info(rec, STR_SENT);
}

static void	ft_allocate_for_str(t_receive_info *rec)
{
	int	str_len;

	str_len = rec->decimal;
	rec->str = (char *)malloc((str_len + 1) * sizeof(char));
	if (rec->str == NULL)
	{
		ft_putstr_fd("Failed to memory allocate!\n", STDERR_FILENO);
		exit(MEM_ERROR);
	}
	rec->str[str_len] = '\0';
	ft_init_receive_info(rec, STR_LEN_SENT);
}

static void	ft_receive_signal(int	signal)
{
	g_sig = signal;
}

int	main(void)
{
	static t_receive_info	rec;

	ft_printf("PID : %d\n", getpid());
	signal(SIGUSR1, ft_receive_signal);
	signal(SIGUSR2, ft_receive_signal);
	while (true)
	{
		pause();
		rec.decimal += (g_sig - SIGUSR1) << rec.bit_cnt;
		rec.bit_cnt++;
		if (!rec.is_len_sent && rec.bit_cnt == sizeof(size_t) * BYTE)
			ft_allocate_for_str(&rec);
		else if (rec.is_len_sent && rec.bit_cnt == BYTE)
		{
			if (rec.decimal == EOT)
			{
				ft_print_str(&rec);
				continue ;
			}
			rec.str[rec.index] = (char)(rec.decimal);
			rec.index++;
			ft_init_receive_info(&rec, CHAR_SENT);
		}
	}
}
