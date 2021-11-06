/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:48 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/06 10:55:31 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_list	*g_list;

void	execute_bin(t_list *cmd_head, char **envp, t_env **env)
{
	int pid;
	int i;
	char **prefix;
	char *file_name;
	int	pipe_open;
	int fd;

	(void)envp;
	init_execute_bin();

	char	**my_envp = allocate_envp(*env);

	pipe_open = 0;
	fd = 0;
	
	if (cmd_head->next && cmd_head->next->type == PIPE)
	{
		pipe_open = 1;
		if (pipe(cmd_head->pipe) == -1)
			error_check("");
	}
	pid = fork();
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
			if (close(cmd_head->prev->pipe[1]) == -1)
				error_check("");
		}
		if (cmd_head->cmd_table == NULL)
		{
			exit(70);
		}
		else if (check_builtin(&cmd_head) == 1)
		{
			t_list	*cmd_list;

			cmd_list = g_list->cmd_list;
			while (cmd_list)
			{
				if (cmd_list->type == PIPE && cmd_head->type == PIPE)
					break ;
				if (cmd_list->next)
					cmd_list = cmd_list->next;
				else
				{
					all_free(&g_list);
					exit(0);
				}
			}
			check_cmd(&g_list, env, &cmd_head);			
			all_free(&g_list);
			exit(0);
		}
		else
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			while ((*env) != NULL)
			{
				i = 0;
				prefix = ft_split((*env)->value, ':');
				while (prefix[i] != NULL)
				{
					if (cmd_head->cmd_table[0][0] != '/')
					{
						prefix[i] = ft_strjoin(prefix[i], "/");
						file_name = ft_strjoin(prefix[i], cmd_head->cmd_table[0]);
					}
					else
					{
						char **check;

						check = ft_split(cmd_head->cmd_table[0], '/');
						while (*check != NULL)
							(check)++; // check free
						check--;
						file_name = cmd_head->cmd_table[0];
						cmd_head->cmd_table[0] = *check;
					}
					i++;
					if (execve(file_name, cmd_head->cmd_table, my_envp) < 0)
					{
						free(file_name);
						continue ;
					}
				}
				free(prefix);
				(*env) = (*env) -> next; // env free
			}
			ft_putstr_fd("command not found : ", 2);
			ft_putstr_fd(cmd_head->cmd_table[0], 2);
			ft_putstr_fd("\n", 2);
			exit(NOT_FOUND);
		}
	}
	else
	{
		if (cmd_head->type != PIPE && cmd_head->cmd_table)
			check_cmd(&g_list, env, &cmd_head);
		if (pipe_open)
		{
			close(cmd_head->pipe[1]);
		}
		if (cmd_head->type == PIPE && cmd_head->prev)
		{
			close(cmd_head->prev->pipe[0]);
		}
		if (cmd_head->infile != 0)
			close(cmd_head->infile);
		else if (cmd_head->outfile != 0)
			close(cmd_head->outfile);
		for (int j = 0; my_envp[j] != NULL; j++)
			free(my_envp[j]);
		free(my_envp);
	}
	return ;
}
