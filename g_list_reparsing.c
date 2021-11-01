/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_list_reparsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:56:08 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/01 18:56:09 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(char **cmd_table)
{
	int size;

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
	t_list *del;

	del = *lst;
	*lst = (*lst)->prev;
	(*lst)->next = (*lst)->next->next;
	if ((*lst)->next)
		(*lst)->next->prev = (*lst);
	free(del->cmd_table[0]);
	free(del->cmd_table);
	free(del);
}

void	re_parsing(t_list **g_list)
{
	t_list	*cmd;
	char	**cmd_table;
	int		size;
	int		i;

	cmd = NULL;
	cmd_table = NULL;
	size = 0;
	while (*g_list)
	{
		i = 0;
		if (((*g_list)->type == TOKEN_END && cmd == NULL))
		{
			cmd = (*g_list);
		}
		else if (((*g_list)->type == TOKEN_END && cmd != NULL))
		{
			size = get_size(cmd->cmd_table);
			cmd_table = malloc(sizeof(char *) * (size + 2));
			while ((cmd)->cmd_table[i] != NULL)
			{
				cmd_table[i] = ft_strdup(cmd->cmd_table[i]);
				i++;
			}
			cmd_table[i++] = ft_strdup((*g_list)->cmd_table[0]);
			cmd_table[i] = NULL;
			for (int j = 0; cmd->cmd_table[j] != NULL; j++)
			{
				free(cmd->cmd_table[j]);
				cmd->cmd_table[j] = NULL;
			}
			free(cmd->cmd_table);
			cmd->cmd_table = cmd_table;
			ft_lstdelone(g_list);
		}
		else if ((*g_list)->type == PIPE)
		{
			cmd = (*g_list);
		}
		if ((*g_list)->next == NULL)
			return ;
		(*g_list) = (*g_list) -> next;
	}
}

