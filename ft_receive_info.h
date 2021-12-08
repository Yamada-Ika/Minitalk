/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_receive_info.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 22:26:10 by iyamada           #+#    #+#             */
/*   Updated: 2021/12/07 04:26:26 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RECEIVE_INFO_H
# define FT_RECEIVE_INFO_H

typedef struct s_receive_info
{
	int	bit_count;
	int	decimal_num;
	int	client_pid;
	int	is_pid_sent;
	int	is_str_len_sent;
	int	str_index;
}	t_receive_info;

#endif
