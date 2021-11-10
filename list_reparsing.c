/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_reparsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:56:08 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/11 03:26:20 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char **cmd_table)
{
	int	size;

	size = 0;
	if (cmd_table == NULL)
		return (size);
	while (cmd_table[size] != NULL)
	{
		size++;
	}
	return (size);
}

void	ft_lstdelone(t_list **lst)
{
	t_list	*del;

	del = *lst;
	*lst = (*lst)->prev;
	(*lst)->next = (*lst)->next->next;
	if ((*lst)->next)
		(*lst)->next->prev = (*lst);
	free(del->cmd_table[0]);
	free(del->cmd_table);
	free(del);
}

void	init_reparse(t_list **cmd, char ***cmd_table)
{
	*cmd = NULL;
	*cmd_table = NULL;
}

void	re_parsing(t_list **list)
{
	t_list	*cmd;
	char	**cmd_table;
	int		i;

	init_reparse(&cmd, &cmd_table);
	while (*list)
	{
		i = 0;
		if (((*list)->type == TOKEN_END && cmd == NULL))
			cmd = (*list);
		else if (((*list)->type == TOKEN_END && cmd != NULL))
		{
			cmd_table = ft_malloc(8 * (get_size(cmd->cmd_table) + 2));
			while ((cmd)->cmd_table[i] != NULL)
				cmd_table[i] = ft_strdup(cmd->cmd_table[i]), i++;
			cmd_table[i++] = ft_strdup((*list)->cmd_table[0]);
			free_cmd_table(cmd->cmd_table), cmd->cmd_table = cmd_table;
			cmd_table[i] = NULL, ft_lstdelone(list);
		}
		else if ((*list)->type == PIPE)
			cmd = (*list);
		if ((*list)->next == NULL)
			return ;
		(*list) = (*list)->next;
	}
}
