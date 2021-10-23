/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:19:06 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/21 18:41:06 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *buf)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (!ret)
	{
		ft_putstr_fd("malloc error\n", 1);
		exit(errno);
		return (NULL);
	}
	ret->cmd_table = malloc(sizeof(char *) * 2);
	ret->cmd_table[0] = buf;
	ret->cmd_table[1] = NULL;
	ret->next = NULL;
	ret->prev = NULL;
	ret->type = 0;
	ret->length = 0;
	ret->exit_status = 0;
	return (ret);
}
