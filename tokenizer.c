/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:07 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/02 18:03:35 by yoyoo            ###   ########.fr       */
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
		error_check("");
		**buf = '\0';
	}
	size = ft_strlen(*buf);
	temp = malloc(sizeof(char) * (size + 2));
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

int	open_double_quote(char **line, char **buf, t_env **env)
{
	(*line)++;
	//(void)env;
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
		else if (**line == '$')
		{
			//printf("fewf");
			line = change_dollar(line, buf, *env);
			if (*buf == NULL)
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

int	is_white_space(char **line, char **buf, int *type)
{
	if (**line == '\0')
		return (-1);
	if (is_space(**line) == 0)
		return (1);
	if (g_list && (ft_lstlast(g_list)->type == TOKEN_END || ft_lstlast(g_list)->type == PIPE) && *type != PIPE)
	{
		add_arg(buf);
	}
	if (*buf != NULL)
	{
		make_node(buf, *type);
		*type = TOKEN_END;
	}
	while (is_space(**line))
	{
		(*line)++;
	}
	(*line)--;
	return (0);
}

char	**change_dollar(char **line, char **buf, t_env *env)
{
	char	*check;

	
	(*line)++;
	if (!**line || **line == '\"')
	{	
		(*line)--;
		return (line);
	}
	if (is_space(**line))
	{
		make_string('$', buf);
		(*line)--;
		return (line);
	}
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
		
		if (**line == '\"')
			break ;
		
		check = ft_strjoin_ch(check, **line);
		
		(*line)++;
		if (**line == '\"')
			break ;
		
		//else
		//	break ;
	}
	//(void)buf;
	//char *tmp;
	while (env)
	{
		if (ft_strcmp(check, (env)->key) == 0)
		{
			
			*buf = ft_strjoin(*buf, (env)->value);
			free(check);
			check = NULL;
			//write(1, *buf, ft_strlen(*buf));
			(*line)--;
			return (line);
		}
		if ((env)->next)
			env = (env)->next;
		else
			break ;
		
	}
	
	
	free(check);
	check = NULL;
	(*line)--;
	return (line);
}

int	is_dollar(char **line, char **buf)
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
		make_string(' ', buf);
		while (is_space(**line))
			(*line)++;
		(*line)--;
		return (0);
	}
	else
	{
		(*line)--;
		while (1)
		{
			make_string(**line, buf);
			if (**line != 0)
				(*line)++;	
			else
			{
				(*line)--;
				break ;
			}
			if (is_space(**line))
			{
				(*line)--;
				break ;
			}	
		}
		
	}
	return (1);
}

int	tokenizer(char *line, t_env **env)
{
	int		error_num;
	static	char	*buf;
	static	char	*redir_buf;
	int		type;

	buf = NULL;
	redir_buf = NULL;
	type = TOKEN_END;
	while (*line)
	{
		if (*line == '\"')
			error_num = open_double_quote(&line, &buf, env);
		else if (*line == '\'')
			error_num = open_single_quote(&line, &buf);
		else if (*line == ' ')
		{
			error_num = is_white_space(&line, &buf, &type);
		}
		else if (*line == ';' || *line == '\\')
		{
			error_num = -1;
		}
		else if (*line == '$')
		{
			error_num = is_dollar(&line, &buf);
		}
		else if (*line == '|')
		{
			// | 먼저 나왔을 경우, || 방지
			if ((buf == NULL && g_list == NULL) || *(line + 1) == '|')
				return (-1);
			else if (buf != NULL)
				make_node(&buf, TOKEN_END);
			buf = ft_strdup("|");
			make_node(&buf, CRITERIA);
			line++;
			error_num = is_white_space(&line, &buf, &type);
			if (error_num == 0)
				line++;
			if (*line == '|' && *line == '\0')
				return (-1);
			type = PIPE;
			line--;
		}
		else if (*line == '<')
		{
			if (buf != NULL)
				make_node(&buf, TOKEN_END);
			line++;
			if (*line == '<')
			{
				line++;
				error_num = is_white_space(&line, &redir_buf, &type);
				if (error_num == 0)
					line++;
				if (*line != ' ' && *line != '\t' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
				{
					while (*line != ' ' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
					{
						make_string(*line, &buf);
						line++;
					}
					make_node(&buf, HEREDOC);
					line--;
				}
				else
					return (-1);
			}
			else
			{
				error_num = is_white_space(&line, &redir_buf, &type);
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
					line--;
				}
				else
					return (-1);
			}
			/*if (buf != NULL)
			 *    make_node(&buf, TOKEN_END);
			 *line++;
			 *error_num = is_white_space(&line, &redir_buf, &type);
			 *if (error_num == 0)
			 *    line++;
			 *if (*line != ' ' && *line != '\t' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
			 *{
			 *    while (*line != ' ' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
			 *    {
			 *        make_string(*line, &buf);
			 *        line++;
			 *    }
			 *    make_node(&buf, L_REDIR);
			 *    line--;
			 *}
			 *else
			 *    return (-1);*/
		}
		else if (*line == '>')
		{
			if (buf != NULL)
				make_node(&buf, TOKEN_END);
			line++;
			if (*line == '>')
			{
				line++;
				error_num = is_white_space(&line, &redir_buf, &type);
				if (error_num == 0)
					line++;
				if (*line != ' ' && *line != '\t' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
				{
					while (*line != ' ' && *line != '<' && *line != '>' && *line != '|' && *line != '\0')
					{
						make_string(*line, &buf);
						line++;
					}
					make_node(&buf, A_REDIR);
					line--;
				}
				else
					return (-1);
			}
			else
			{
				error_num = is_white_space(&line, &redir_buf, &type);
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
					line--;
				}
				else
					return (-1);
			}
		}
		else
		{
			error_num = make_string(*line, &buf);
		}
		if (error_num < 0)
			break ;
		line++;
	}
	if (g_list && (ft_lstlast(g_list)->type == TOKEN_END || ft_lstlast(g_list)->type == PIPE) && type != PIPE)
		add_arg(&buf);
	make_node(&buf, type);
	return (error_num);
}
