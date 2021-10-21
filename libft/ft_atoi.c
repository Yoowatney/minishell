/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:19:39 by yoyoo             #+#    #+#             */
/*   Updated: 2021/09/17 21:55:10 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int			sign;
	long long	i;

	sign = 1;
	i = 0;
	while (*str == ' ' || *str == '\n' || *str == '\f'
		|| *str == '\t' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
	{
		str++;
		sign *= -1;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		i *= 10;
		i += (sign) * ((*(str++) - '0'));
	}
	return (i);
}
