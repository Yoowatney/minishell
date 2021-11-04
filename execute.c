/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:48 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/02 17:59:14 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_list	*g_list;

void	execute_bin(t_list *cmd_head, char **envp, t_env **env, char **cmdline)
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
		pipe(cmd_head->pipe);
		error_check("");
	}
	if ((pid = fork()) < 0)
	{
		error_check("");
	}
	else if (pid == 0)
	{
		if (cmd_head->next && cmd_head->next->type == PIPE && dup2(cmd_head->pipe[1], 1) < 0)
		{
			error_check("");
		}
		if (cmd_head->type == PIPE && cmd_head->infile == 0 && dup2(cmd_head->prev->pipe[0], 0) < 0)
		{
			error_check("");
		}
		if (cmd_head->cmd_table == NULL)
		{
			exit(0);
		}
		else if (check_builtin(&cmd_head) == 1)
		{
			if (check_cmd(&g_list, cmdline, env, &cmd_head) == 3)
			{
				all_free(&g_list, cmdline);
				exit(2);
			}
			all_free(&g_list, cmdline);
			exit(1);
			/*
			while (g_list->cmd_list)
			{
				if (g_list->cmd_list->type == PIPE)
				{
					check_cmd(&g_list, cmdline, my_envp);
					exit(1);
					break ;
				}
				if (g_list->cmd_list->next != NULL)
					g_list->cmd_list = g_list->cmd_list->next;
				else
				{
					all_free(&g_list, cmdline);
					exit(3);
				}
			}*/
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
						prefix[i] = ft_strjoin(prefix[i], "/"); // prefix free됨
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
						free(file_name); // file_name[0] free
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
		// sleep 10 | ls 수정
		/*pid_t	dead;
		 *while (1)
		 *{
		 *    dead = wait(&i);
		 *    if (pid == dead || dead == -1)
		 *        while (wait(NULL) != -1)
		 *            continue ;
		 *    break ;
		 *}*/
		waitpid(pid, &g_list->exit_status, 0);
		printf("exit : %d\n", g_list->exit_status);
/*
		if (g_list->exit_status == 256)
		{
			check_cmd(&g_list, cmdline, my_envp);
		}*/
		if (g_list->exit_status == 512)
		{
			check_cmd(&g_list, cmdline, env, &cmd_head);
		}
		if (pipe_open)
		{
			close(cmd_head->pipe[1]);
			if (!(cmd_head->next))
				close(cmd_head->pipe[0]);
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
