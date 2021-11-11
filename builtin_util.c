/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:39:31 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 17:39:32 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_equal_sign(char *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i])
	{
		if (cmd_table[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	check_alpha(char *cmd_table)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((cmd_table[i] >= 65 && cmd_table[i] <= 90)
			|| (cmd_table[i] >= 97 && cmd_table[i] <= 122)
			|| (cmd_table[i] >= 48 && cmd_table[i] <= 57)
			|| (cmd_table[i] == '_'))
		{
			i++;
			continue ;
		}
		if (cmd_table[i + 1] && cmd_table[i + 1] == '='
			&& cmd_table[i] == '+')
			return (1);
		else if (cmd_table[i] && cmd_table[i] == '=')
			return (1);
		else if (!cmd_table[i])
			return (1);
		else if (cmd_table[i])
			return (-1);
	}
	return (1);
}

int	check_num(char *cmd_table)
{
	if (cmd_table[0] >= 48 && cmd_table[0] <= 57)
		return (-1);
	if (cmd_table[0] == '=')
		return (-1);
	return (1);
}

int	check_identifier(char *cmd_table, t_list **cmd_head, int *ret)
{
	if (check_num(cmd_table) == -1
		|| check_alpha(cmd_table) == -1)
	{
		print_valid(cmd_head, cmd_table);
		*ret = 1;
		return (-1);
	}
	return (1);
}
