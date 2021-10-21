/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:02:25 by yoyoo             #+#    #+#             */
/*   Updated: 2021/07/16 22:31:53 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return ((char *)ft_calloc(sizeof(char), 1));
	if (ft_strlen(s) - start < len)
		ret = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (i < len && s[start] != '\0')
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}
