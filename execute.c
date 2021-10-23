/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:48 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/23 14:38:44 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute_bin(t_list *g_list, char **envp, t_env *env)
{
	int pid;
	int i;
	char **prefix;
	char *file_name;
	int	pipe_open;

	(void)envp;
	init_execute_bin();

	char	**my_envp = allocate_envp(env);

	pipe_open = 0;
	if (g_list -> type == PIPE || (g_list -> prev && g_list -> prev -> type == PIPE))
	{
		pipe_open = 1;
		pipe(g_list->pipe);
		error_check();
	}
	if ((pid = fork()) < 0)
		error_check();
	else if (pid == 0)
	{
		if (g_list -> type == PIPE && dup2(g_list->pipe[1], 1) < 0)
		{
			error_check();
		}
		if (g_list -> prev && g_list -> prev ->type == PIPE && dup2(g_list -> prev -> pipe[0], 0) < 0)
		{
			error_check();
		}
		else
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			while (env != NULL)
			{
				i = 0;
				prefix = ft_split(env->value, ':');
				while (prefix[i] != NULL)
				{
					if (g_list->cmd_table[0][0] != '/')
					{
						prefix[i] = ft_strjoin(prefix[i], "/"); // prefix free됨
						file_name = ft_strjoin(prefix[i], g_list->cmd_table[0]);
					}
					else
					{
						char **check;

						check = ft_split(g_list->cmd_table[0], '/');
						while (*check != NULL)
							(check)++; // check free
						check--;
						file_name = g_list->cmd_table[0];
						g_list->cmd_table[0] = *check;
					}
					i++;
					if (execve(file_name, g_list->cmd_table, my_envp) < 0)
					{
						free(file_name); // file_name[0] free
						continue ;
					}
				}
				free(prefix);
			   	env = env -> next; // env free
			}
			ft_putstr_fd("command not found : ", 2);
			ft_putstr_fd(g_list->cmd_table[0], 2);
			ft_putstr_fd("\n", 2);
			exit(NOT_FOUND);
		}
	}
	else
	{
		waitpid(pid, &i, 0); // 여기가 문제인듯
		if (pipe_open)
		{
			close(g_list->pipe[1]);
			if (!(g_list -> next) || g_list -> type == TOKEN_END)
				close(g_list->pipe[0]);
		}
		if (g_list -> prev && g_list -> prev -> type == PIPE)
			close(g_list -> prev -> pipe[0]);
		for (int j = 0; my_envp[j] != NULL; j++)
			free(my_envp[j]);
		free(my_envp);
	}
	return ;
}
