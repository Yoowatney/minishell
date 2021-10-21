/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:13:53 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:35:25 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	size_t	i;

	i = 0;
	if ((!dest && !src))
		return (0);
	if (dest < src)
	{
		while (i < num)
		{
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	else
	{
		while (num)
		{
			*((unsigned char *)dest + num - 1)
				= *((unsigned char *)src + num - 1);
			num--;
		}
	}
	return ((void *)dest);
}
