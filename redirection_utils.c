/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:03:31 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/11 03:36:17 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		ft_close(fd);
		ft_dup2(copy[1], STDOUT_FILENO);
	}
}

void	right_redir(t_list *cmd_head, t_list *redir_head, int fd, int i)
{
	fd = open(redir_head->cmd_table[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		error_check("");
	cmd_head->outfile = fd;
	ft_dup2(fd, STDOUT_FILENO);
}

void	append_redir(t_list *cmd_head, t_list *redir_head, int fd, int i)
{
	fd = open(redir_head->cmd_table[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		error_check("");
	cmd_head->outfile = fd;
	ft_dup2(fd, STDOUT_FILENO);
}

int	left_redir(t_list *redir_head, int *fd, int i, int copy[])
{
	*fd = open(redir_head->cmd_table[i], O_RDONLY);
	if (*fd == -1)
		error_check(redir_head->cmd_table[i]);
	if (errno == 2)
	{
		ft_close(copy[0]);
		return (-1);
	}
	ft_dup2(*fd, STDIN_FILENO);
	return (0);
}

void	heredoc_redir(t_list *cmd_head, t_list *redir_head, int fd, int i)
{
	char	*str;

	fd = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_check("");
	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL || ft_strncmp(str, redir_head->cmd_table[i],
				ft_strlen(redir_head->cmd_table[i])) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str)), write(fd, "\n", 1);
		free(str);
	}
	ft_close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
		error_check("");
	cmd_head->infile = fd;
	ft_dup2(fd, STDIN_FILENO);
}
