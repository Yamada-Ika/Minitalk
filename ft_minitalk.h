/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:15:54 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/08 11:29:40 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# define SLEEP_TIME 1000
# define BYTE 8
# define EOT 0x04
# define PID_MIN 0
# define KILL_FAILE -1
# define SEND_FAILE -1
# define SEND_SUCCESS 1

# include <sys/types.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>

int	ft_pow(int base, int expo);

#endif
