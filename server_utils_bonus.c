/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:40:02 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 16:40:25 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

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
