/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:56:18 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 16:24:14 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_sub(char *s1, char *s2, char **ret)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		(*ret)[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		(*ret)[i] = *s2;
		s2++;
		i++;
	}
	(*ret)[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (ft_strdup(s2));
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
	{
		exit(errno);
	}
	ft_strjoin_sub(s1, s2, &ret);
	free(s1);
	return (ret);
}
