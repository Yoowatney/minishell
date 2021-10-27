/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:18:22 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/25 17:38:29 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (new == NULL)
	{
		ft_putstr_fd("malloc error\n", 1);
		ft_lstclear(lst);
		exit(MALLOC_ERROR);
	}
	ptr = ft_lstlast(*lst);
	ptr->next = new;
	new->prev = ptr;
}
