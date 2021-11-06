/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:49:20 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/06 10:02:31 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(ft_strlen(s1) + 1);
	if (!ret)
	{
		exit(errno);
	}
	while (i < ft_strlen(s1))
	{
		ret[i] = *(s1 + i);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
