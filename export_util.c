/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:38:52 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 17:38:53 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_plus_equal(char *cmd_table)
{
	int	i;

	i = 0;
	if (cmd_table[i] == '+' || cmd_table[i] == '=')
		return (-1);
	i++;
	while (cmd_table[i])
	{
		if (cmd_table[i + 1])
		{	
			if (cmd_table[i] == '+' && cmd_table[i + 1] == '+')
				return (-1);
			else if (cmd_table[i] == '+' && cmd_table[i + 1] == '=')
				return (i);
		}
		i++;
	}
	return (0);
}

t_env	*check_key(t_env *env, char *key)
{
	t_env	*env_key;

	env_key = env;
	while ((env_key)->key)
	{
		if (ft_strcmp((env_key)->key, key) == 0)
			return (env_key);
		if ((env_key)->next)
			(env_key) = (env_key)->next;
		else
			break ;
	}
	return (NULL);
}

void	free_str(char **export_str)
{
	char	*temp;
	int		i;

	i = 0;
	while (export_str[i])
	{
		temp = export_str[i];
		free(temp);
		i++;
	}
	free(export_str);
}

char	*get_export_key(char *cmd_table)
{
	char	*ret;
	int		index;

	index = check_plus_equal(cmd_table);
	if (index >= 1)
	{
		cmd_table[index] = '\0';
		ret = ft_strdup(cmd_table);
		cmd_table[index] = '+';
	}
	else if (index == -1)
		return (NULL);
	else
	{
		index = check_equal_sign(cmd_table);
		if (index == -1)
			return (NULL);
		else
		{
			cmd_table[index] = '\0';
			ret = ft_strdup(cmd_table);
			cmd_table[index] = '=';
		}
	}
	return (ret);
}

char	*get_export_value(char *cmd_table)
{
	char	*ret;
	int		index;

	index = check_plus_equal(cmd_table);
	if (index >= 1)
	{
		index += 2;
		ret = ft_strdup(&cmd_table[index]);
	}
	else if (index == -1)
		return (NULL);
	else
	{
		index = check_equal_sign(cmd_table);
		if (index == -1)
			return (NULL);
		else
		{
			index++;
			ret = ft_strdup(&cmd_table[index]);
		}
	}
	return (ret);
}
