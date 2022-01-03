/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:26:13 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/03 14:01:38 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

volatile sig_atomic_t	g_signal;

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
	ft_putendl_fd(rec->str, STDOUT_FILENO);
	free(rec->str);
	ft_init_receive_info(rec, STR_SENT);
}

static void	ft_allocate_for_str(t_receive_info *rec)
{
	size_t	str_len;

	str_len = rec->decimal;
	rec->str = (char *)malloc((str_len + 1) * sizeof(char));
	if (rec->str == NULL)
		ft_error("Failed to memory allocate!", MEM_ERROR);
	rec->str[str_len] = '\0';
	ft_init_receive_info(rec, STR_LEN_SENT);
}

static void	ft_get_signal(int	signal)
{
	g_signal = signal;
}

int	main(void)
{
	static t_receive_info	rec;

	ft_printf("PID : %d\n", getpid());
	signal(SIGUSR1, ft_get_signal);
	signal(SIGUSR2, ft_get_signal);
	while (true)
	{
		pause();
		rec.decimal += (g_signal - SIGUSR1) << rec.bit_cnt;
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
			rec.str[rec.index] = rec.decimal;
			rec.index++;
			ft_init_receive_info(&rec, CHAR_SENT);
		}
	}
}
