/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:41:19 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 18:43:21 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_cmd(t_list **cmd_head)
{
	char	*cmd_table;
	int		i;

	i = 1;
	while ((*cmd_head)->cmd_table[i])
	{
		cmd_table = (*cmd_head)->cmd_table[i];
		if (check_equal_sign(cmd_table) == -1)
		{
			no_file_env(cmd_head, cmd_table);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	extra_cmd(t_list **cmd_head)
{
	char	**cmd_table;
	int		i;

	cmd_table = (*cmd_head)->cmd_table;
	i = 1;
	while (cmd_table[i])
	{
		if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
		{
			ft_putstr_fd(cmd_table[i], (*cmd_head)->pipe[1]);
			ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
		}
		else
		{
			ft_putstr_fd(cmd_table[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (1);
}

void	print_envp(char ***my_envp, t_list **cmd_head)
{
	ft_putstr_fd(**my_envp, (*cmd_head)->pipe[1]);
	ft_putchar_fd('\n', (*cmd_head)->pipe[1]), (*my_envp)++;
}

int	builtin_env(char **my_envp, t_list **cmd_head)
{
	if (check_env_cmd(cmd_head) == -1)
		return (127);
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		while (*my_envp)
		{
			print_envp(&my_envp, cmd_head);
			if (*my_envp == NULL)
				break ;
		}
		if ((*cmd_head)->cmd_table[1])
			extra_cmd(cmd_head);
	}
	else
	{
		while (*my_envp)
		{
			ft_putstr_fd(*my_envp, 1), ft_putchar_fd('\n', 1), my_envp++;
			if (*my_envp == NULL)
				break ;
		}
		if ((*cmd_head)->cmd_table[1])
			extra_cmd(cmd_head);
	}
	return (0);
}
