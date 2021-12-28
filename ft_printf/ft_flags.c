/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 00:21:42 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 13:57:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_flags(t_flags *flags)
{
	flags->is_minus = false;
	flags->is_zero = false;
	flags->is_dot = false;
	flags->is_sharp = false;
	flags->is_space = false;
	flags->is_plus = false;
	flags->conv = '\0';
	flags->width = 0;
	flags->prec = 0;
}

void	ft_set_conversion(const char *format, size_t index, t_flags *flags)
{
	if (format[index] == 'c')
		flags->conv = 'c';
	else if (format[index] == 's')
		flags->conv = 's';
	else if (format[index] == 'p')
		flags->conv = 'p';
	else if (format[index] == 'd' || format[index] == 'i')
		flags->conv = 'd';
	else if (format[index] == 'u')
		flags->conv = 'u';
	else if (format[index] == 'x')
		flags->conv = 'x';
	else if (format[index] == 'X')
		flags->conv = 'X';
	else if (format[index] == '%')
		flags->conv = '%';
}

void	ft_consider_flags_priority(t_flags *flags)
{
	if (flags->conv != '\0' && ft_strchr("diuxX", flags->conv) \
		&& flags->is_dot && flags->is_zero)
		flags->is_zero = false;
	if (flags->is_minus && flags->is_zero)
		flags->is_zero = false;
	if (flags->is_plus && flags->is_space)
		flags->is_space = false;
}

bool	ft_is_conversion(const char *format, size_t index, t_flags *flags)
{
	if (format[index] != '\0' && ft_strchr("cspduixX%", format[index]))
	{
		ft_set_conversion(format, index, flags);
		ft_consider_flags_priority(flags);
		return (true);
	}
	return (false);
}

size_t	ft_get_flags(const char *format, size_t index, t_flags *flags)
{
	size_t	init_index;

	init_index = index;
	while (format[index] != '\0' && !ft_is_conversion(format, index, flags))
	{
		if (format[index] == '-')
			flags->is_minus = true;
		else if (format[index] == '0' && index == init_index)
			flags->is_zero = true;
		else if (format[index] == '.')
			flags->is_dot = true;
		else if (format[index] == '#')
			flags->is_sharp = true;
		else if (format[index] == ' ')
			flags->is_space = true;
		else if (format[index] == '+')
			flags->is_plus = true;
		else if (ft_isdigit(format[index]) && !flags->is_dot)
			flags->width = flags->width * 10 + format[index] - '0';
		else if (ft_isdigit(format[index]) && flags->is_dot)
			flags->prec = flags->prec * 10 + format[index] - '0';
		index++;
	}
	return (index);
}
