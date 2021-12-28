/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_cspdiu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:11:37 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 13:57:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printf_c(va_list *ap, size_t write_len, t_flags *flags)
{
	int	c;

	c = va_arg(*ap, int);
	write_len = ft_printf_c_with_flags(flags, write_len, c);
	if (write_len == ERROR)
		return (ERROR);
	return (write_len);
}

size_t	ft_printf_s(va_list *ap, size_t write_len, t_flags *flags)
{
	char	*str;
	char	*heap_str;

	str = va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	heap_str = ft_strdup(str);
	if (heap_str == NULL)
		return (ERROR);
	write_len = ft_print_with_flags(flags, &heap_str, write_len);
	ft_free_s((void **)&heap_str);
	if (write_len == ERROR)
		return (ERROR);
	return (write_len);
}

size_t	ft_printf_p(va_list *ap, size_t write_len, t_flags *flags)
{
	char	*hex_str;

	hex_str = \
		ft_ultoa_base((unsigned long)va_arg(*ap, void *), "0123456789abcdef");
	if (hex_str == NULL)
		return (ERROR);
	write_len = ft_print_with_flags(flags, &hex_str, write_len);
	ft_free_s((void **)&hex_str);
	if (write_len == ERROR)
		return (ERROR);
	return (write_len);
}

size_t	ft_printf_di(va_list *ap, size_t write_len, t_flags *flags)
{
	char	*num;

	num = ft_itoa(va_arg(*ap, int));
	if (num == NULL)
		return (ERROR);
	write_len = ft_print_with_flags(flags, &num, write_len);
	ft_free_s((void **)&num);
	if (write_len == ERROR)
		return (ERROR);
	return (write_len);
}

size_t	ft_printf_u(va_list *ap, size_t write_len, t_flags *flags)
{
	char	*num;

	num = ft_uitoa(va_arg(*ap, unsigned int));
	if (num == NULL)
		return (ERROR);
	write_len = ft_print_with_flags(flags, &num, write_len);
	ft_free_s((void **)&num);
	if (write_len == ERROR)
		return (ERROR);
	return (write_len);
}
