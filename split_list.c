/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:33:28 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 04:40:23 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_cmd_node(t_list *go, t_list *ret)
{
	while (go)
	{
		if (go->type == TOKEN_END || go->type == PIPE)
		{
			ret->cmd_table = duplicate_table(go->cmd_table);
			ret->type = go->type;
			ret->length = go->length;
			ret->exit_status = go->exit_status;
			ret->infile = go->infile;
			ret->outfile = go->outfile;
		}
		else if (go->type == CRITERIA)
			ret = ret -> next;
		if (go->next != NULL)
			go = go->next;
		else
			break ;
	}
	return ;
}

void	free_cmd_table(char **cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table && cmd_table[i] != NULL)
	{
		free(cmd_table[i]);
		cmd_table[i] = NULL;
		i++;
	}
	free(cmd_table);
}

void	fill_redir_node(char **redir_table, char **cmd_table, char *element)
{
	int	i;

	i = 0;
	while (cmd_table && cmd_table[i] != NULL)
	{
		redir_table[i] = ft_strdup(cmd_table[i]);
		i++;
	}
	redir_table[i++] = ft_strdup(element);
	redir_table[i] = NULL;
}

void	fill_type_table(int *new, int *old, int element)
{
	int	i;

	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = element;
	new[i] = 0;
	free(old);
}

void	split_redir_node(t_list *go, t_list *ret)
{
	char	**redir_table;
	int		*redir_type_table;

	init_redir_node(&redir_table, &redir_type_table);
	while (go)
	{
		if (choice_condition(go->type) == 1)
		{
			redir_table = ft_malloc(sizeof(char *)
					* (get_size(ret->cmd_table) + 2));
			fill_redir_node(redir_table, ret->cmd_table, go->cmd_table[0]);
			free_cmd_table(ret->cmd_table), ret->cmd_table = NULL;
			ret->cmd_table = redir_table;
			redir_type_table = ft_malloc(sizeof(int)
					* (get_file_size(ret->file_type_table) + 2));
			fill_type_table(redir_type_table, ret->file_type_table, go->type);
			ret->file_type_table = redir_type_table;
		}
		else if (choice_condition(go->type) == 0)
			ret = ret->next;
		if (go->next != NULL)
			go = go->next;
		else
			break ;
	}
}
