/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:40:23 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:34:29 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *source, int c, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
	{
		*(char *)dest = *(char *)source;
		dest++;
		i++;
		if (*(unsigned char *)source == (unsigned char)c)
			return (dest);
		source++;
	}
	return (0);
}
