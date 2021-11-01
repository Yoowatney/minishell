#include "minishell.h"

void	make_redir_node(char **buf, int type, t_list **redir_node)
{
	t_list *node;

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
	{
		*redir_node = node;
	}
	else
	{
		ft_lstadd_back(redir_node, node);
	}
}

int	process_redir_node(t_list *redir_head, t_list *cmd_head, int copy[])
{
	int fd;
	int i;

	i = 0;
	copy[0] = dup(STDIN_FILENO);
	copy[1] = dup(STDOUT_FILENO);
	fd = 0;
	while (redir_head->cmd_table && redir_head->cmd_table[i])
	{
		if (redir_head->file_type_table[i] == L_REDIR)
		{
			if (fd != 0)
			{
				close(fd);
				dup2(copy[0], STDIN_FILENO);
			}
			fd = open(redir_head->cmd_table[i], O_RDONLY);
			error_check(redir_head->cmd_table[i]);
			if (errno == 2)
			{
				close(copy[0]);
				return (-1);
			}
			errno = 0;
			cmd_head->infile = fd;
			dup2(fd, STDIN_FILENO);
			error_check("");
		}
		else if (redir_head->file_type_table[i] == R_REDIR)
		{
			if (fd != 0)
			{
				close(fd);
				dup2(copy[1], STDOUT_FILENO);
			}
			fd = open(redir_head->cmd_table[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			error_check(redir_head->cmd_table[i]);
			if (errno == 2)
			{
				close(copy[1]);
				return (-1);
			}
			errno = 0;
			cmd_head->outfile = fd;
			dup2(fd, STDOUT_FILENO);
			error_check("");
		}
		i++;
	}
	return (1);
}
