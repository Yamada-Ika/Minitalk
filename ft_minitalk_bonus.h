/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:15:54 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 17:23:27 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_BONUS_H
# define FT_MINITALK_BONUS_H

# define SLEEP_TIME 200
# define BYTE 8
# define EOT 0x04
# define PID_MIN 0
# define ERROR_PID -1
# define KILL_FAILE -1
# define SEND_FAILE -1
# define SEND_SUCCESS 1

// Error status
# define ARG_ERROR 1
# define SEND_ERROR 2
# define MEM_ERROR 1
# define SIG_ERROR 3

// flags
# define STR_LEN_SENT 0
# define CHAR_SENT 1
# define STR_SENT 2

# include "ft_printf/ft_printf.h"
# include <sys/types.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_receive_info
{
	int		bit_cnt;
	size_t	decimal;
	bool	is_len_sent;
	char	*str;
	size_t	index;
}	t_receive_info;

void	ft_init_receive_info(t_receive_info *rec, int flag);
void	ft_error(char *fmt, int status);

#endif
