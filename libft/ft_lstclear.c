/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 22:30:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 16:23:42 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*ptr;
	int		i;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		ptr = *lst;
		i = 0;
		if (ptr->cmd_table)
		{
			while (ptr->cmd_table[i] != NULL)
			{
				free(ptr->cmd_table[i]);
				ptr->cmd_table[i] = NULL;
				i++;
			}
			free(ptr->cmd_table);
			ptr->cmd_table = NULL;
		}
		if (ptr->file_type_table)
			free(ptr->file_type_table);
		*lst = (*lst)->next;
		free(ptr), ptr = NULL;
	}
}
