/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:59:30 by jlim              #+#    #+#             */
/*   Updated: 2021/11/11 03:25:48 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned int	g_exit_status;

void	rewind_env(t_env **env)
{
	while ((*env)->prev)
		(*env) = (*env)->prev;
}

void	ft_envclear(t_env **env)
{
	t_env	*ptr;

	if (!*env)
		return ;
	while ((*env)->next)
	{
		ptr = *env;
		if (ptr)
		{
			free(ptr->env_line);
			ptr->env_line = NULL;
			free(ptr->key);
			ptr->key = NULL;
			free(ptr->value);
			ptr->value = NULL;
		}
		*env = (*env)->next;
		free(ptr);
		ptr = NULL;
	}
}

void	all_free(t_list **list)
{
	rewind_list(list);
	rewind_list(&((*list)->cmd_list));
	rewind_list(&((*list)->redir_list));
	ft_lstclear(&((*list)->cmd_list));
	ft_lstclear(&((*list)->redir_list));
	free((*list)->cmdline);
	(*list)->cmd_list = NULL;
	(*list)->redir_list = NULL;
	ft_lstclear(list);
	(*list) = NULL;
}

int	check_exit_num(char *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i])
	{
		if (cmd_table[i] >= 48 && cmd_table[i] <= 57)
			i++;
		else
			return (-1);
	}
	return (1);
}

int	builtin_exit(t_list **list, t_env **env, t_list **cmd_head)
{
	g_exit_status = 0;
	if ((*cmd_head)->cmd_table[1] && (*cmd_head)->cmd_table[2])
	{
		if (check_exit_num((*cmd_head)->cmd_table[1]) == 1)
			return (error_exit1(cmd_head));
	}
	if ((*cmd_head)->cmd_table[1])
	{
		if (check_exit_num((*cmd_head)->cmd_table[1]) == -1)
			g_exit_status = (unsigned char)error_exit2(cmd_head);
		else
			g_exit_status = (unsigned char)(ft_atoi((*cmd_head)->cmd_table[1]));
	}
	if (pipe_exist(*list) == 0)
		ft_putstr_fd("exit\n", 2);
	rewind_list(list);
	rewind_list(&(*list)->cmd_list);
	all_free(list);
	rewind_env(env);
	ft_envclear(env);
	exit(g_exit_status);
}
