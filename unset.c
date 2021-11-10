/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:03:08 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 15:03:11 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **check, t_env **tmp, t_env **env)
{
	t_env	*ret;

	ret = *check;
	if (ret == *env)
	{
		free((ret)->env_line);
		free((ret)->key);
		free((ret)->value);
		*check = *tmp;
		*env = *tmp;
		free(ret);
		return ;
	}
	*check = *tmp;
	free((ret)->env_line);
	free((ret)->key);
	free((ret)->value);
	free(ret);
	return ;
}

void	delete_env_util(t_env **check, t_env **tmp)
{
	if ((*check)->prev && (*check)->next)
	{
		(*check)->prev->next = (*check)->next;
		(*check)->next->prev = (*check)->prev;
		*tmp = (*check)->next;
	}
	else if ((*check)->prev)
	{
		(*check)->prev->next = NULL;
		*tmp = (*check)->prev;
	}
	else
	{
		(*check)->next->prev = NULL;
		*tmp = (*check)->next;
	}
}

void	delete_env(t_env **env, char *unset_key)
{
	t_env	*check;
	t_env	*tmp;

	check = *env;
	while (check)
	{
		if (ft_strcmp((check)->key, unset_key) == 0)
		{
			delete_env_util(&check, &tmp);
			free_env(&check, &tmp, env);
		}
		if ((check)->next)
			(check) = (check)->next;
		else
			break ;
	}
}

int	check_unset_alpha(char *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i])
	{
		if ((cmd_table[i] >= 65 && cmd_table[i] <= 90)
			|| (cmd_table[i] >= 97 && cmd_table[i] <= 122)
			|| (cmd_table[i] >= 48 && cmd_table[i] <= 57)
			|| (cmd_table[i] == '_'))
		{
			i++;
			continue ;
		}
		if (cmd_table[i])
			return (-1);
	}
	return (1);
}

int	builtin_unset(t_list **cmd_head, t_env **env)
{
	int		i;
	char	*cmd_table;
	int		ret;

	i = 1;
	ret = 0;
	while ((*cmd_head)->cmd_table[i])
	{
		cmd_table = (*cmd_head)->cmd_table[i];
		if (check_num(cmd_table) == -1
			|| check_unset_alpha(cmd_table) == -1)
		{
			print_valid(cmd_head, cmd_table);
			ret = 1;
			i++;
			continue ;
		}
		delete_env(env, (*cmd_head)->cmd_table[i]);
		i++;
	}
	return (ret);
}
