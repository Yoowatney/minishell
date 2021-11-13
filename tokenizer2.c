/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:14:41 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/13 20:26:17 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipe_node(char **buf, char **line, int *type, t_list **list)
{
	int		error_num;
	char	*temp;

	temp = *line;
	error_num = 0;
	if ((*buf == NULL && *list == NULL) || *(temp + 1) == '|')
		return (-1);
	else if (*buf != NULL)
		make_node(buf, TOKEN_END, list);
	*buf = ft_strdup("|");
	make_node(buf, CRITERIA, list);
	(*line)++;
	error_num = is_white_space(line, buf, type, list);
	if (error_num == 0)
		(*line)++;
	if (**line == '|' || **line == '\0')
		return (-1);
	*type = PIPE;
	(*line)--;
	return (error_num);
}

int	make_A_redir_node(char **buf, char **line, int *type, t_list **list)
{
	(*line)++;
	if (is_white_space(line, buf, type, list) == 0)
		(*line)++;
	if (**line != ' ' && **line != '\t' && **line != '<' && **line != '>'
		&& **line != '|' && **line != '\0')
	{
		while (**line != ' ' && **line != '<' && **line != '>'
			&& **line != '|' && **line != '\0')
		{
			make_string(**line, buf);
			(*line)++;
		}
		make_node(buf, HEREDOC, list);
		(*line)--;
	}
	else
		return (-1);
	return (0);
}

int	make_L_redir_node(char **buf, char **line, int *type, t_list **list)
{
	if (*buf != NULL)
		make_node(buf, TOKEN_END, list);
	(*line)++;
	if (**line == '<')
	{
		if (make_A_redir_node(buf, line, type, list) < 0)
			return (-1);
	}
	else
	{
		if (is_white_space(line, buf, type, list) == 0)
			(*line)++;
		if (**line != ' ' && **line != '\t' && **line != '<'
			&& **line != '>' && **line != '|' && **line != '\0')
		{
			while (**line != ' ' && **line != '<' && **line != '>'
				&& **line != '|' && **line != '\0')
				make_string(**line, buf), (*line)++;
			make_node(buf, L_REDIR, list), (*line)--;
		}
		else
			return (-1);
	}
	return (0);
}

int	make_H_redir_node(char **buf, char **line, int *type, t_list **list)
{
	(*line)++;
	if (is_white_space(line, buf, type, list) == 0)
		(*line)++;
	if (**line != ' ' && **line != '\t' && **line != '<' && **line != '>'
		&& **line != '|' && **line != '\0')
	{
		while (**line != ' ' && **line != '<' && **line != '>'
			&& **line != '|' && **line != '\0')
		{
			make_string(**line, buf);
			(*line)++;
		}
		make_node(buf, A_REDIR, list);
		(*line)--;
	}
	else
		return (-1);
	return (0);
}

int	make_R_redir_node(char **buf, char **line, int *type, t_list **list)
{
	if (*buf != NULL)
		make_node(buf, TOKEN_END, list);
	(*line)++;
	if (**line == '>')
	{
		if (make_H_redir_node(buf, line, type, list) < 0)
			return (-1);
	}
	else
	{
		if (is_white_space(line, buf, type, list) == 0)
			(*line)++;
		if (**line != ' ' && **line != '\t' && **line != '<'
			&& **line != '>' && **line != '|' && **line != '\0')
		{
			while (**line != ' ' && **line != '<' && **line != '>'
				&& **line != '|' && **line != '\0')
				make_string(**line, buf), (*line)++;
			make_node(buf, R_REDIR, list), (*line)--;
		}
		else
			return (-1);
	}
	return (0);
}
