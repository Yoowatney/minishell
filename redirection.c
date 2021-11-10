/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:16:43 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 03:34:41 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_redir_node(char **buf, int type, t_list **redir_node)
{
	t_list	*node;

	if (*buf == NULL)
	{
		*buf = ft_strdup("");
		return ;
	}
	node = ft_lstnew(*buf);
	node->length = 1;
	node->type = type;
	*buf = NULL;
	if (*redir_node == NULL)
		*redir_node = node;
	else
		ft_lstadd_back(redir_node, node);
}

int	process_redir_node(t_list *redir_head, t_list *cmd_head, int copy[])
{
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	copy[0] = ft_dup(STDIN_FILENO);
	copy[1] = ft_dup(STDOUT_FILENO);
	while (redir_head->cmd_table && redir_head->cmd_table[i])
	{
		if (redir_head->file_type_table[i] == L_REDIR)
		{
			close_L_fd(fd, copy);
			if (left_redir(redir_head, &fd, i, copy) == -1)
				return (-1);
			cmd_head->infile = fd;
		}
		else if (redir_head->file_type_table[i] == HEREDOC)
			close_L_fd(fd, copy), heredoc_redir(cmd_head, redir_head, fd, i);
		else if (redir_head->file_type_table[i] == R_REDIR)
			close_R_fd(fd, copy), right_redir(cmd_head, redir_head, fd, i);
		else if (redir_head->file_type_table[i] == A_REDIR)
			close_R_fd(fd, copy), append_redir(cmd_head, redir_head, fd, i);
		i++;
	}
	return (1);
}
