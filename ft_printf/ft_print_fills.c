/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fills.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 02:22:20 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 13:57:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_fill_c(char c, size_t fill_num)
{
	size_t	write_fill_len;

	write_fill_len = 0;
	while (write_fill_len < fill_num)
	{
		ft_putchar(c);
		write_fill_len++;
	}
	return (write_fill_len);
}

void	ft_put_prefix(t_flags *flags, char *str)
{
	if (str[0] == '0' && flags->conv != 'p')
		return ;
	if (flags->conv == 'p' || (flags->is_sharp && flags->conv == 'x'))
		ft_putstr("0x");
	if (flags->is_sharp && flags->conv == 'X')
		ft_putstr("0X");
}
