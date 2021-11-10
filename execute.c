/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:48 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 14:18:27 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	exit_status;

int	pipe_exist(t_list *g_list)
{
	t_list	*cmd_list;

	cmd_list = g_list->cmd_list;
	while (cmd_list)
	{
		if (cmd_list->type == PIPE)
			return (1);
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		else
			break ;
	}
	return (0);
}

// envp 삭제
void	execute_bin(t_list *cmd_head, t_env **env, t_list **g_list)
{
	int		pid;
	int		pipe_open;
	int		fd;
	char	**my_envp;
   
	pipe_open = 0;
	fd = 0;
	my_envp = allocate_envp(*env);
	init_execute_bin();
	if (cmd_head->next && cmd_head->next->type == PIPE)
	{
		pipe_open = 1;
		if (pipe(cmd_head->pipe) == -1)
			error_check("");
	}
	pid = fork();
	cmd_head->pid = pid;
	if (pid < 0)
	{
		error_check("");
	}
	else if (pid == 0)
	{
		if (cmd_head->next && cmd_head->next->type == PIPE && cmd_head->outfile == 0)
		{
			if (dup2(cmd_head->pipe[1], 1) == -1)
				error_check("");
			if (close(cmd_head->pipe[0]) == -1)
				error_check("");
		}
		if (cmd_head->type == PIPE && cmd_head->infile == 0)
		{
			if (dup2(cmd_head->prev->pipe[0], 0) == -1)
				error_check("");
		}
		if (cmd_head->cmd_table == NULL)
		{
			exit(0);
		}
		else if (check_builtin(&cmd_head) == 1)
		{
			int	pipe;
		
			pipe = pipe_exist(*g_list);
			
			if (pipe == 1)
			{
				exit_status = (unsigned char)check_cmd(g_list, env, &cmd_head, my_envp);
				all_free(g_list);
				exit((int)(exit_status));
			}			
			all_free(g_list);
			exit(0);
		}
		else
		{
			execute(cmd_head, *g_list, env, my_envp);
		}
	}
	else
	{
		int	pipe;

		pipe = pipe_exist(*g_list);
		if (pipe != 1 && cmd_head->type != PIPE && cmd_head->cmd_table)
			exit_status = (unsigned char)check_cmd(g_list, env, &cmd_head, my_envp);
		if (pipe_open)
			close(cmd_head->pipe[1]);
		if (cmd_head->type == PIPE && cmd_head->prev)
			close(cmd_head->prev->pipe[0]);
		if (cmd_head->infile != 0)
			close(cmd_head->infile);
		else if (cmd_head->outfile != 0)
			close(cmd_head->outfile);
		free_cmd_table(my_envp);
	}
	return ;
}
