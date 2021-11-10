/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:11:29 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 09:11:30 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	exit_status;

char	**change_dollar_util(char **line, char **buf)
{
	char	*exit_str;
	int		i;

	i = 0;
	if (!**line || **line == '\"')
	{	
		make_string('$', buf);
		(*line)--;
	}
	if (is_space(**line))
	{
		make_string('$', buf);
		(*line)--;
	}
	if (**line == '?')
	{
		exit_str = ft_itoa((int)exit_status);
		while (exit_str[i])
		{
			make_string(exit_str[i], buf);
			i++;
		}
		free(exit_str);
	}
	return (line);
}

char	**change_dollar_util2(char **check, t_env *env, char **buf, char **line)
{
	while (env)
	{
		if (ft_strcmp(*check, env->key) == 0)
		{
			*buf = ft_strjoin(*buf, env->value);
			free(*check);
			*check = NULL;
			(*line)--;
			return (line);
		}
		if (env->next)
			env = env->next;
		else
			break ;
	}
	if (*buf == NULL)
		make_string('\0', buf);
	free(*check);
	*check = NULL;
	(*line)--;
	return (line);
}

char	**change_dollar(char **line, char **buf, t_env *env)
{
	char	*check;

	(*line)++;
	change_dollar_util(line, buf);
	check = (char *)malloc(sizeof(char));
	*check = 0;
	while ((!is_space(**line) || !**line) && **line != '\'')
	{
		if (!**line)
		{
			(*line)--;
			free(check);
			check = NULL;
			return (line);
		}
		check = ft_strjoin_ch(check, **line);
		(*line)++;
		if (**line == '\"')
			break ;
	}
	return (change_dollar_util2(&check, env, buf, line));
}
