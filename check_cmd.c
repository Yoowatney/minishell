/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:15:59 by jlim              #+#    #+#             */
/*   Updated: 2021/11/11 03:24:47 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_list **cmd_head)
{
	if (ft_strcmp((*cmd_head)->cmd_table[0], "echo") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "cd") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "pwd") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "export") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "unset") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "env") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "exit") == 0)
		return (1);
	return (0);
}

int	cmd_builtin(t_list **list, t_env **env, t_list **cmd_head, char **my_envp)
{
	int		ret;

	ret = 0;
	if (ft_strcmp((*cmd_head)->cmd_table[0], "echo") == 0)
		ret = builtin_echo(cmd_head);
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "cd") == 0)
		ret = builtin_cd(cmd_head, my_envp, env);
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "pwd") == 0)
		ret = builtin_pwd(cmd_head);
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "export") == 0)
		ret = builtin_export(cmd_head, env);
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "unset") == 0)
		ret = builtin_unset(cmd_head, env);
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "env") == 0)
		ret = builtin_env(my_envp, cmd_head);
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "exit") == 0)
		ret = builtin_exit(list, env, cmd_head);
	return (ret);
}
