#include "minishell.h"

void	right_redir(t_list *cmd_head, t_list *redir_head, int fd, int copy[], int i)
{
	if (fd != 0)
	{
		close(fd);
		if (dup2(copy[1], STDOUT_FILENO) == -1)
			error_check("");
	}
	if ((fd = open(redir_head->cmd_table[i], O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		error_check("");
	cmd_head->outfile = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_check("");
}

void	append_redir(t_list *cmd_head, t_list *redir_head, int fd, int copy[], int i)
{
	if (fd != 0)
	{
		close(fd);
		if (dup2(copy[1], STDOUT_FILENO) == -1)
			error_check("");
	}
	if ((fd = open(redir_head->cmd_table[i], O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		error_check("");
	cmd_head->outfile = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_check("");
}

