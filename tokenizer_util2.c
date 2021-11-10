/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:16:48 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/11 03:28:01 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_single_quote(char **line, char **buf, t_list **list)
{
	(*line)++;
	while (1)
	{
		if (**line == '\'')
		{
			if (*buf == NULL)
			{
				*buf = ft_strdup("\0");
				make_node(buf, TOKEN_END, list);
			}
			return (0);
		}
		else if (**line == '\0')
			return (-1);
		else
			make_string(**line, buf);
		(*line)++;
	}
	return (1);
}

int	open_double_quote(char **line, char **buf, t_env **env, t_list **list)
{
	(*line)++;
	while (1)
	{
		if (**line == '\"')
		{
			if (*buf == NULL)
				*buf = ft_strdup("\0"), make_node(buf, TOKEN_END, list);
			return (0);
		}
		else if (**line == '\0')
			return (-1);
		else if (**line == '$')
		{
			line = change_dollar(line, buf, *env);
			if (**line == '\"')
				(*line)--;
			if (*buf == NULL)
				return (-1);
		}
		else
			make_string(**line, buf);
		(*line)++;
	}
	return (1);
}

int	is_white_space(char **line, char **buf, int *type, t_list **list)
{
	if (**line == '\0')
		return (-1);
	if (is_space(**line) == 0)
		return (1);
	if (*list && (ft_lstlast(*list)->type == TOKEN_END
			|| ft_lstlast(*list)->type == PIPE) && *type != PIPE)
		add_arg(buf, *list);
	if (*buf != NULL)
	{
		make_node(buf, *type, list);
		*type = TOKEN_END;
	}
	while (is_space(**line))
		(*line)++;
	(*line)--;
	return (0);
}

int	is_dollar(char **line, char **buf, t_env **env)
{
	if ((*line)++ && **line == '\0')
	{
		make_string('$', buf);
		(*line)--;
		return (0);
	}
	if (is_space(**line) == 1 || **line == 0)
	{
		make_string('$', buf);
		(*line)--;
		return (0);
	}
	else
	{
		(*line)--;
		line = change_dollar2(line, buf, *env);
		if (*buf == NULL)
			return (-1);
	}
	return (1);
}
