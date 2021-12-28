/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:15:54 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/28 18:52:25 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# define SLEEP_TIME 200
# define BYTE 8
# define EOT 0x04
# define PID_MIN 0
# define KILL_FAILE -1

// Error status
//  server
# define MEM_ERROR 1
//  client
# define ARG_ERROR 1
# define SEND_ERROR 2

// flags
# define STR_LEN_SENT 0
# define CHAR_SENT 1
# define STR_SENT 2

# include <sys/types.h>
# include <signal.h>
# include "ft_printf/ft_printf.h"

typedef struct s_receive_info
{
	int		bit_cnt;
	size_t	decimal;
	bool	is_len_sent;
	char	*str;
	size_t	index;
}	t_receive_info;

void	ft_error(char *fmt, int status);

#endif
