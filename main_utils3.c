/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:36:21 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 19:00:23 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_status;

int	main_tokenizer(char **cmdline, t_env **env, t_list **g_list)
{
	if (cmdline_start(cmdline) == NULL)
		return (1);
	if (tokenizer(*cmdline, env, g_list) < 0)
	{
		ft_putstr_fd("pasing error\n", 2);
		g_exit_status = PARSE;
		if (*g_list != NULL)
			(*g_list)->cmdline = *cmdline, all_free(g_list);
		else
			free(*cmdline);
		system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");
		return (1);
	}
	reparse_rewind(g_list);
	return (0);
}

void	split_list(t_list **cmd_head, t_list **redir_head,
		t_list *g_list, char *cmdline)
{
	split_cmd(cmd_head, g_list);
	split_redir(redir_head, g_list);
	g_list->cmd_list = *cmd_head;
	g_list->redir_list = *redir_head;
	g_list->cmdline = cmdline;
}

void	execute_process(t_list **cmd_head, t_env **env, t_list **g_list,
		t_list **redir_head)
{
	int	copy[2];

	while ((*cmd_head) != NULL)
	{
		if (process_redir_node(*redir_head, *cmd_head, copy) < 0)
			break ;
		execute_bin(*cmd_head, env, g_list);
		ft_dup2(copy[0], STDIN_FILENO);
		ft_dup2(copy[1], STDOUT_FILENO);
		close(copy[0]);
		close(copy[1]);
		if ((*cmd_head)->next)
		{
			(*cmd_head) = (*cmd_head)->next;
			(*redir_head) = (*redir_head)->next;
		}
		else
			break ;
	}
}

void	wait_process(t_list **cmd_head, t_list **g_list)
{
	rewind_list(cmd_head);
	while (waitpid((*cmd_head)->pid, &(*cmd_head)->exit_status, 0) > 0)
	{
		if ((*cmd_head)->next)
			*cmd_head = (*cmd_head)->next;
	}
	if (g_exit_status == 0)
		g_exit_status = (unsigned char)((*cmd_head)->exit_status / 256);
	all_free(g_list);
}
