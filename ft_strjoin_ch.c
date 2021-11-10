/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:36:39 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 19:37:48 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_ch(char *s1, char c)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	if (!s1 || !c)
		return (NULL);
	ret = ft_malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!ret)
		return (NULL);
	tmp = ret;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}	
	ret[i] = c;
	i++;
	ret[i] = 0;
	free(s1);
	s1 = NULL;
	return (tmp);
}
