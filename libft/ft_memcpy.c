/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:13:37 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:35:03 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	unsigned long	i;

	i = 0;
	if (!dest && !source)
		return (dest);
	while (i < num)
	{
		*((unsigned char *)dest + i) = *(unsigned char *)source;
		i++;
		source++;
	}
	return (dest);
}
