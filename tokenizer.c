/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:07 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/21 15:38:14 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_list	*g_list;
static	char	*buf = NULL;

void	link_node(char **buf, int type)
{
	t_list	*node;

	node = ft_lstnew(*buf);
	node -> length = 1;
	node -> type = type;
	*buf = NULL;
	ft_lstadd_back(&g_list, node);
}

void	make_node(char **buf, int type)
{
	t_list *node;

	if (*buf == NULL && g_list != NULL) // 공백과 pipe가 연달아 나올때
	{
		node = malloc(sizeof(t_list));
		node -> length = 0;
		node -> cmd_table = NULL;
		node -> type = 0;
		node -> next = NULL;
		node -> prev = g_list;
		g_list -> next = node;
		return ;
	}
	else if (*buf == NULL) // "   ls"
		return ;
	node = ft_lstnew(*buf);
	node -> length = 1;
	node -> type = type;
	*buf = NULL;
	if (g_list == NULL)
		g_list = node;
	else
		ft_lstadd_back(&g_list, node);
}

int	add_arg(char **buf)
{
	char	**temp;
	int		i;

	i = 0;
	if (*buf == NULL)
		return (1);
	temp = malloc(sizeof(char *) * (g_list->length + 2));
	while (i < g_list->length)
	{
		temp[i] = g_list->cmd_table[i];
		i++;
	}
	if (g_list->length > 0)
		free(g_list->cmd_table);
	temp[i++] = *buf;
	temp[i] = NULL;
	*buf = NULL;
	g_list->cmd_table = temp;
	g_list->length++;
	return (1);
}

int	make_string(char c)
{
	int			size;
	char		*temp;

	if (buf == NULL)
	{
		buf = malloc(sizeof(char));
		*buf = '\0';
	}
	size = ft_strlen(buf);
	temp = malloc(sizeof(char) * (size + 2));
	ft_strlcpy(temp, buf, size + 1);
	temp[size] = c;
	temp[size + 1] = '\0';
	free(buf);
	buf = temp;
	return (1);
}

int	open_single_quote(char **line)
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
			make_string(**line);
		(*line)++;
	}
	return (1);
}

int	open_double_quote(char **line)
{
	(*line)++;
	while (1)
	{
		if (**line == '\"')
		{
			return (0); // okay
		}
		else if (**line == '\0')
		{
			return (-1); // error
		}
		else
		{
			make_string(**line);
		}
		(*line)++;
	}
	return (1);
}

int	is_white_space(char **line)
{
	if (g_list == NULL)
		make_node(&buf, TOKEN_END);
	else
		add_arg(&buf);
	while (is_space(**line))
	{
		(*line)++;
	}
	(*line)--;
	return (0);
}
// make node : buf == NULL -> empty node 생성 
// || buf != NULL ->  buf 들어간 node 생성
int	tokenizer(char *line)
{
	int	error_num;

	while (*line)
	{
		if (g_list && g_list->type > TOKEN_END)
		{
			make_node(&buf, TOKEN_END);
			g_list = g_list -> next;
		}
		if (*line == '\"')
			error_num = open_double_quote(&line);
		else if (*line == '\'')
			error_num = open_single_quote(&line);
		else if (*line == ' ')
		{
			error_num = is_white_space(&line);
		}
		else if (*line == ';' || *line == '\\')
		{
			error_num = -1;
		}
		else if (*line == '|')
		{
			if ((buf == NULL && g_list == NULL) || *(line + 1) == '|')
				return (-1);
			if (g_list == NULL)
				make_node(&buf, PIPE);
			else
			{
				add_arg(&buf);
				g_list->type = PIPE;
			}
		}
		else
		{
			error_num = make_string(*line);
		}
		if (error_num < 0)
			break ;
		line++;
	}
	if (g_list == NULL) // 첫인자 생성
	{
		make_node(&buf, TOKEN_END);
	}
	else if (g_list -> type > TOKEN_END)
	{
		return (-1);
	}
	else
		add_arg(&buf);
	return (error_num);
}
