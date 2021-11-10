/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:07 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 14:33:29 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*extern t_list *g_list;*/
extern unsigned char	exit_status;

void	make_node(char **buf, int type, t_list **g_list)
{
	t_list *node;

	if (*buf == NULL)
		return ;
	node = ft_lstnew(*buf);
	node -> length = 1;
	node -> type = type;
	*buf = NULL;
	if (*g_list == NULL)
	{
		*g_list = node;
	}
	else
	{
		ft_lstadd_back(g_list, node);
	}
}

int	add_arg(char **buf, t_list *g_list)
{
	char	**temp;
	int		i;

	i = 0;
	if (*buf == NULL)
		return (1);
	temp = malloc(sizeof(char *) * (ft_lstlast(g_list)->length + 2));
	if (temp == NULL)
		error_check("");
	while (i < ft_lstlast(g_list)->length)
	{
		temp[i] = ft_lstlast(g_list)->cmd_table[i];
		i++;
	}
	if (ft_lstlast(g_list)->length > 0)
		free(ft_lstlast(g_list)->cmd_table);
	temp[i++] = *buf;
	temp[i] = NULL;
	*buf = NULL;
	ft_lstlast(g_list)->cmd_table = temp;
	ft_lstlast(g_list)->length++;
	return (1);
}

int	make_string(char c, char **buf)
{
	int			size;
	char		*temp;

	if (*buf == NULL)
	{
		(*buf) = malloc(sizeof(char));
		if (*buf == NULL)
			error_check("");
		**buf = '\0';
	}
	size = ft_strlen(*buf);
	temp = malloc(sizeof(char) * (size + 2));
	if (temp == NULL)
		error_check("");
	ft_strlcpy(temp, *buf, size + 1);
	temp[size] = c;
	temp[size + 1] = '\0';
	free(*buf);
	
	*buf = temp;
	return (1);
}

int	open_single_quote(char **line, char **buf)
{
	(*line)++;
	while (1)
	{
		if (**line == '\'')
		{
			return (0);
		}
		else if (**line == '\0')
		{
			return (-1);
		}
		else
			make_string(**line, buf);
		(*line)++;
	}
	return (1);
}

int	open_double_quote(char **line, char **buf, t_env **env)
{
	(*line)++;
	while (1)
	{
		if (**line == '\"')
			return (0);
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

int	is_white_space(char **line, char **buf, int *type, t_list **g_list)
{
	if (**line == '\0')
		return (-1);
	if (is_space(**line) == 0)
		return (1);
	if (*g_list && (ft_lstlast(*g_list)->type == TOKEN_END || ft_lstlast(*g_list)->type == PIPE) && *type != PIPE)
		add_arg(buf, *g_list);
	if (*buf != NULL)
	{
		make_node(buf, *type, g_list);
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

int	tokenizer(char *line, t_env **env, t_list **g_list)
{
	int		error_num;
	static	char	*buf;
	int		type;

	buf = NULL, type = TOKEN_END;
	while (*line)
	{
		if (*line == '\"')
			error_num = open_double_quote(&line, &buf, env);
		else if (*line == '\'')
			error_num = open_single_quote(&line, &buf);
		else if (*line == ' ')
			error_num = is_white_space(&line, &buf, &type, g_list);
		else if (*line == ';' || *line == '\\')
			error_num = -1;
		else if (*line == '$')
			error_num = is_dollar(&line, &buf, env);
		else if (*line == '|')
			error_num = make_pipe_node(&buf, &line, &type, g_list);
		else if (*line == '<')
			error_num = make_L_redir_node(&buf, &line, &type, g_list);
		else if (*line == '>')
			error_num = make_R_redir_node(&buf, &line, &type, g_list);
		else
			error_num = make_string(*line, &buf);
		if (error_num < 0)
		{
			free(buf), buf = NULL;
			return (-1);
		}
		line++;
	}
	if (*g_list && (ft_lstlast(*g_list)->type == TOKEN_END || ft_lstlast(*g_list)->type == PIPE) && type != PIPE)
		add_arg(&buf, *g_list);
	make_node(&buf, type, g_list);
	return (error_num);
}
