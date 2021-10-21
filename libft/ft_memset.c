/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:50:36 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:35:36 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned long	i;

	i = 0;
	while (i < num)
	{
		*((unsigned char *)ptr + i) = (unsigned char)value;
		i++;
	}
	return (ptr);
}
