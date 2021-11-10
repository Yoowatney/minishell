/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:33:20 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 19:31:05 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*empty_node(void)
{
	t_list	*node;
	int		i;

	node = ft_malloc(sizeof(t_list));
	if (node == NULL)
		error_check("");
	i = 0;
	node->cmd_table = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->type = EMPTY;
	node->file_type_table = NULL;
	node->length = 0;
	node->exit_status = 0;
	node->infile = 0;
	node->outfile = 0;
	return (node);
}

char	**duplicate_table(char **cmd_table)
{
	int		size;
	char	**ret;

	size = 0;
	while (cmd_table[size] != NULL)
	{
		size++;
	}
	ret = ft_malloc(sizeof(char *) * (size + 1));
	size = 0;
	while (cmd_table[size] != NULL)
	{
		ret[size] = ft_strdup(cmd_table[size]);
		size++;
	}
	ret[size] = NULL;
	return (ret);
}

int	count_pipe(t_list *go)
{
	int	size;

	size = 0;
	while (go)
	{
		if (ft_strncmp(go->cmd_table[0], "|", 1) == 0)
			size++;
		if (go->next != NULL)
			go = go->next;
		else
			break ;
	}
	return (size);
}

t_list	*create_list(t_list *go)
{
	int		size;
	t_list	*head;

	size = count_pipe(go) + 1;
	head = NULL;
	while (size--)
	{
		ft_lstadd_back(&head, empty_node());
	}
	return (head);
}

int	get_file_size(int *files)
{
	int	size;

	size = 0;
	if (files == NULL)
		return (size);
	while (files[size] != 0)
	{
		size++;
	}
	return (size);
}
