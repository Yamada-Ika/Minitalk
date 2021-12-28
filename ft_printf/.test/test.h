/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:58:50 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/27 13:59:07 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include "../ft_printf.h"

# define BRACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define PURPLE			"\033[35m"
# define CYAN			"\033[36m"
# define COLOR_RESET	"\033[0m"

void ft_check_value(int ft_printf_result, int printf_result)
{
	if (ft_printf_result == printf_result)
	{
		printf(GREEN);
		printf("result value : OK!");
		printf(COLOR_RESET);
		printf("\n");
	}
	else
	{
		printf(RED);
		printf("result value : KO!");
		printf(COLOR_RESET);
		printf("\n");
		printf(YELLOW);
		printf("ft_printf : %d\n", ft_printf_result);
		printf("printf    : %d", printf_result);
		printf(COLOR_RESET);
		printf("\n");
	}
}

#endif
