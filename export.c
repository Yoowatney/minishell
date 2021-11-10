/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:17:23 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 19:37:04 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sign(t_list **cmd_head, char *cmd_table, int *ret, int *i)
{
	if (check_identifier(cmd_table, cmd_head, ret) == -1)
	{
		(*i)++;
		return (-1);
	}
	if (check_equal_sign(cmd_table) == -1)
	{
		(*i)++;
		return (-1);
	}
	return (1);
}

char	*find_key(t_env **env, char *cmd_table, t_env **new)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = get_export_key(cmd_table);
	*new = check_key(*env, key);
	if (*new && check_plus_equal(cmd_table) >= 1)
	{
		free((*new)->env_line);
		value = get_export_value(cmd_table);
		(*new)->value = ft_strjoin((*new)->value, value);
		tmp = ft_strjoin_ch(ft_strdup(key), '=');
		(*new)->env_line = ft_strjoin(tmp, (*new)->value);
		free(value);
	}
	else if (*new)
	{
		free((*new)->value);
		free((*new)->env_line);
		(*new)->value = get_export_value(cmd_table);
		(*new)->env_line = ft_strdup(cmd_table);
	}
	return (key);
}

void	get_new_key(char *cmd_table, t_env **new, char *new_key, t_env **env)
{
	char	*tmp;

	*new = ft_malloc(sizeof(t_env));
	error_check("");
	(*new)->next = NULL;
	(*new)->prev = NULL;
	(*new)->key = get_export_key(cmd_table);
	(*new)->value = get_export_value(cmd_table);
	tmp = ft_strjoin_ch(ft_strdup(new_key), '=');
	(*new)->env_line = ft_strjoin(tmp, (*new)->value);
	env_add_back(env, *new);
}

int	builtin_export(t_list **cmd_head, t_env **env)
{
	t_env	*new;
	char	*cmd_table;
	char	*new_key;
	int		ret;
	int		i;

	i = 1;
	ret = 0;
	if ((*cmd_head)->cmd_table[i])
	{
		while ((*cmd_head)->cmd_table[i])
		{		
			cmd_table = (*cmd_head)->cmd_table[i];
			if (check_sign(cmd_head, cmd_table, &ret, &i) == -1)
				continue ;
			new_key = find_key(env, cmd_table, &new);
			if (!new)
				get_new_key(cmd_table, &new, new_key, env);
			free(new_key);
			i++;
		}
	}
	else
		print_export(env, cmd_head);
	return (ret);
}
