/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:06:36 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/17 13:23:58 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_printf_converted_str(const char *format,
	va_list *ap, size_t write_len, t_flags *flags)
{
	if (*format == 'c')
		write_len = ft_printf_c(ap, write_len, flags);
	else if (*format == 's')
		write_len = ft_printf_s(ap, write_len, flags);
	else if (*format == 'p')
		write_len = ft_printf_p(ap, write_len, flags);
	else if (*format == 'd' || *format == 'i')
		write_len = ft_printf_di(ap, write_len, flags);
	else if (*format == 'u')
		write_len = ft_printf_u(ap, write_len, flags);
	else if (*format == 'x')
		write_len = ft_printf_lower_x(ap, write_len, flags);
	else if (*format == 'X')
		write_len = ft_printf_upper_x(ap, write_len, flags);
	else if (*format == '%')
		write_len = ft_printf_percent(write_len, flags);
	return (write_len);
}

static int	ft_printf_helper(const char *format, va_list *ap)
{
	size_t	write_len;
	size_t	i;
	t_flags	flags;

	write_len = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			ft_init_flags(&flags);
			i = ft_get_flags(format, ++i, &flags);
			write_len = ft_printf_converted_str(&format[i], ap, \
				write_len, &flags);
		}
		else
			write_len += ft_fill_c(format[i], CHAR_NUM);
		if (write_len >= INT_MAX)
			return (ERROR_STATUS);
		i++;
	}
	return ((int)write_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_printf_helper(format, &ap);
	va_end(ap);
	return (ret);
}
