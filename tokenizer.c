/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:07 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/27 20:43:09 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_list *g_list;

void	make_node(char **buf, int type)
{
	t_list *node;

	if (*buf == NULL)
	    return ;
	node = ft_lstnew(*buf);
	node -> length = 1;
	node -> type = type;
	*buf = NULL;
	if (g_list == NULL)
	{
		g_list = node;
	}
	else
	{
		ft_lstadd_back(&g_list, node);
	}
}

int	add_arg(char **buf)
{
	char	**temp;
	int		i;

	i = 0;
	if (*buf == NULL)
		return (1);
	temp = malloc(sizeof(char *) * (ft_lstlast(g_list)->length + 2));
	error_check();
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
		error_check();
		**buf = '\0';
	}
	size = ft_strlen(*buf);
	temp = malloc(sizeof(char) * (size + 2));
	error_check();
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
			return (0); // okay
		}
		else if (**line == '\0')
		{
			return (-1); // error
		}
		else
			make_string(**line, buf);
		(*line)++;
	}
	return (1);
}

int	open_double_quote(char **line, char **buf)
{
	(*line)++;
	while (1)
	{
		if (**line == '\"')
		{
			return (0);
		}
		else if (**line == '\0')
		{
			return (-1);
		}
		else
		{
			make_string(**line, buf);
		}
		(*line)++;
	}
	return (1);
}

int	is_white_space(char **line, char **buf)
{
	if (**line == '\0')
		return (-1);
	if (is_space(**line) == 0)
		return (1);
	if (g_list && ft_lstlast(g_list)->type == TOKEN_END)
		add_arg(buf);
	make_node(buf, TOKEN_END);
	while (is_space(**line))
	{
		(*line)++;
	}
	(*line)--;
	return (0);
}

int	tokenizer(char *line)
{
	int	error_num;
	static	char	*buf;

	buf = NULL;
	while (*line)
	{
		if (*line == '\"')
			error_num = open_double_quote(&line, &buf);
		else if (*line == '\'')
			error_num = open_single_quote(&line, &buf);
		else if (*line == ' ')
		{
			error_num = is_white_space(&line, &buf);
		}
		else if (*line == ';' || *line == '\\')
		{
			error_num = -1;
		}
		else if (*line == '|')
		{
			if ((buf == NULL && g_list == NULL) || *(line + 1) == '|')
				return (-1);
			line++;
			error_num = is_white_space(&line, &buf);
			if (error_num == 0)
				line++;
			// white space나오기전까지 node생성
			if (*line != ' ' && *line != '\t' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
			{
				while (*line != ' ' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
				{
					make_string(*line, &buf);
					line++;
				}
				make_node(&buf, PIPE);
			}
			else
				return (-1);
			// 뭐에 하는 역할이더라..?
			/*if (ft_lstlast(g_list)->type != L_REDIR && ft_lstlast(g_list)->type != R_REDIR)
			 *{
			 *    ft_lstlast(g_list)->type = PIPE;
			 *}*/
		}
		else if (*line == '<')
		{
			if (buf != NULL)
				make_node(&buf, TOKEN_END);
			line++;
			error_num = is_white_space(&line, &buf);
			if (error_num == 0)
				line++;
			if (*line != ' ' && *line != '\t' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
			{
				while (*line != ' ' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
				{
					make_string(*line, &buf);
					line++;
				}
				make_node(&buf, L_REDIR);
			}
			else
				return (-1);
		}
		else if (*line == '>')
		{
			if (buf != NULL)
				make_node(&buf, TOKEN_END);
			line++;
			error_num = is_white_space(&line, &buf);
			if (error_num == 0)
				line++;
			if (*line != ' ' && *line != '\t' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
			{
				while (*line != ' ' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
				{
					make_string(*line, &buf);
					line++;
				}
				make_node(&buf, R_REDIR);
			}
			else
				return (-1);
		}
		else
		{
			error_num = make_string(*line, &buf);
		}
		if (error_num < 0)
			break ;
		line++;
	}
	if (g_list && ft_lstlast(g_list)->type == TOKEN_END)
		add_arg(&buf);
	make_node(&buf, TOKEN_END);
	return (error_num);
}
