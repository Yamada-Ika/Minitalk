/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_receive_info.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 22:26:10 by iyamada           #+#    #+#             */
/*   Updated: 2021/11/20 00:58:25 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RECEIVE_INFO_H
# define FT_RECEIVE_INFO_H

typedef struct s_receive_info
{
	int		bit_count;
	int		decimal_num;
	int		is_str_len_sent;
	char	*str;
	int		index;
}	t_receive_info;

#endif
