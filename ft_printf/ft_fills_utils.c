/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fills_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:27:17 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 13:57:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_abs(long long n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

void	ft_swap_sizet(size_t *num_1, size_t *num_2)
{
	size_t	tmp;

	tmp = *num_1;
	*num_1 = *num_2;
	*num_2 = tmp;
}

void	ft_init_fills(t_fills *fills)
{
	fills->sp_fill = 0;
	fills->zero_fill = 0;
	fills->sp_flag_fill = 0;
	fills->plus_fill = 0;
	fills->minus_fill = 0;
}

void	ft_cut_sign(char **num)
{
	size_t		size;
	long long	abs_num;

	size = ft_strlen_s(*num);
	abs_num = ft_abs(ft_atoll(*num));
	ft_free_s((void **)num);
	*num = ft_lltoa(abs_num);
}
