/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:38:48 by yoyoo             #+#    #+#             */
/*   Updated: 2021/05/25 20:01:24 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(str);
	i = 0;
	while (1)
	{
		if (*str == (unsigned char)c)
			return (str);
		if (i == str_len)
			break ;
		str++;
		i++;
	}
	return (NULL);
}
