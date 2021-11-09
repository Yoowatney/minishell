#include "minishell.h"

int	make_pipe_node(char **buf, t_list **g_list, char **line, int *type)
{
	int	error_num;

	error_num = 0;
	if ((*buf == NULL && g_list == NULL) || **(line + 1) == '|')
		return (-1);
	else if (*buf != NULL)
		make_node(buf, TOKEN_END);
	*buf = ft_strdup("|");
	make_node(buf, CRITERIA);
	(*line)++;
	error_num = is_white_space(line, buf, type);
	if (error_num == 0)
		(*line)++;
	if (**line == '|' || **line == '\0')
		return (-1);
	*type = PIPE;
	(*line)--;
	return (error_num);
}

int	make_A_redir_node(char **buf, char **line, int *type)
{
	(*line)++;
	if (is_white_space(line, buf, type) == 0)
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
		make_node(buf, HEREDOC);
		(*line)--;
	}
	else
		return (-1);
	return (0);
}

int	make_L_redir_node(char **buf, char **line, int *type)
{
	if (*buf != NULL)
		make_node(buf, TOKEN_END);
	(*line)++;
	if (**line == '<')
	{
		if (make_A_redir_node(buf, line, type) < 0)
			return (-1);
	}
	else
	{
		if (is_white_space(line, buf, type) == 0)
			(*line)++;
		if (**line != ' ' && **line != '\t' && **line != '<'
			&& **line != '>' && **line != '|' && **line != '\0')
		{
			while (**line != ' ' && **line != '<' && **line != '>'
				&& **line != '|' && **line != '\0')
				make_string(**line, buf), (*line)++;
			make_node(buf, L_REDIR), (*line)--;
		}
		else
			return (-1);
	}
	return (0);
}

int	make_H_redir_node(char **buf, char **line, int *type)
{
	(*line)++;
	if (is_white_space(line, buf, type) == 0)
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
		make_node(buf, A_REDIR);
		(*line)--;
	}
	else
		return (-1);
	return (0);
}

int	make_R_redir_node(char **buf, char **line, int *type)
{
	if (*buf != NULL)
		make_node(buf, TOKEN_END);
	(*line)++;
	if (**line == '>')
	{
		if (make_H_redir_node(buf, line, type) < 0)
			return (-1);
	}
	else
	{
		if (is_white_space(line, buf, type) == 0)
			(*line)++;
		if (**line != ' ' && **line != '\t' && **line != '<'
			&& **line != '>' && **line != '|' && **line != '\0')
		{
			while (**line != ' ' && **line != '<' && **line != '>'
				&& **line != '|' && **line != '\0')
				make_string(**line, buf), (*line)++;
			make_node(buf, R_REDIR), (*line)--;
		}
		else
			return (-1);
	}
	return (0);
}
