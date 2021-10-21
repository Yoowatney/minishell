/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:44:38 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:34:59 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (*(unsigned char *)ptr1 != *(unsigned char *)ptr2)
			return (*(unsigned char *)ptr1 - *(unsigned char *)ptr2);
		else
		{
			i++;
			ptr1++;
			ptr2++;
		}
	}
	return (0);
}
