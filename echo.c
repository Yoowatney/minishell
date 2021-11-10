/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:30:05 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 19:45:02 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_null_util(t_list **cmd_head)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (1)
	{
		if (!(*cmd_head)->cmd_table[i])
			break ;
		if ((*cmd_head)->cmd_table[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**delete_null(t_list **cmd_head)
{
	char	**cmd;
	int		count;
	int		i;

	count = delete_null_util(cmd_head);
	i = 0;
	cmd = ft_malloc(sizeof(char *) * (count + 1));
	count = 0;
	while (1)
	{
		if (!(*cmd_head)->cmd_table[i])
			break ;
		if ((*cmd_head)->cmd_table[i][0] != '\0')
		{
			cmd[count] = ft_strdup((*cmd_head)->cmd_table[i]);
			count++;
		}
		i++;
	}
	cmd[count] = NULL;
	return (cmd);
}

int	only_echo(t_list **cmd_head)
{
	if ((*cmd_head)->cmd_table[1] == NULL)
	{
		if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
		{
			ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
			return (0);
		}
		else
		{
			ft_putchar_fd('\n', 1);
			return (0);
		}
	}
	return (1);
}

int	builtin_echo(t_list **cmd_head)
{
	char	**print;
	int		n_flag;
	int		i;

	i = 0;
	if (only_echo(cmd_head) == 0)
		return (0);
	n_flag = 0;
	print = delete_null(cmd_head), print++, i++;
	while (ft_strcmp(*print, "-n") == 0)
	{
		n_flag = 1, print++, i++;
		if (*print == NULL)
		{
			free_cmd_table(print - i);
			return (0);
		}
	}
	if (echo_util(cmd_head, print, n_flag) == 1)
		return (0);
	else
		echo_util2(print, n_flag);
	free_cmd_table(print - i);
	return (0);
}
