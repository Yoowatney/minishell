/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:31:51 by yoyoo             #+#    #+#             */
/*   Updated: 2021/05/17 16:43:15 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	rear;

	front = 0;
	if (!s1)
		return (0);
	rear = ft_strlen(s1) - 1;
	while (ft_strchr((char *)set, s1[front]) && s1[front])
	{
		front++;
	}
	while (rear && ft_strchr((char *)set, s1[rear]) && s1[rear])
	{
		rear--;
	}
	if (rear == 0)
	{
		return (ft_strdup(""));
	}
	return (ft_substr(s1, front, (rear - front + 1)));
}
