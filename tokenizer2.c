#include "minishell.h"

int	make_pipe_node(char **buf, char **line, int *type, t_list **g_list)
{
	int	error_num;

	error_num = 0;
	if ((*buf == NULL && g_list == NULL) || **(line + 1) == '|')
		return (-1);
	else if (*buf != NULL)
		make_node(buf, TOKEN_END, g_list);
	*buf = ft_strdup("|");
	make_node(buf, CRITERIA, g_list);
	(*line)++;
	error_num = is_white_space(line, buf, type, g_list);
	if (error_num == 0)
		(*line)++;
	if (**line == '|' || **line == '\0')
		return (-1);
	*type = PIPE;
	(*line)--;
	return (error_num);
}

int	make_A_redir_node(char **buf, char **line, int *type, t_list **g_list)
{
	(*line)++;
	if (is_white_space(line, buf, type, g_list) == 0)
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
		make_node(buf, HEREDOC, g_list);
		(*line)--;
	}
	else
		return (-1);
	return (0);
}

int	make_L_redir_node(char **buf, char **line, int *type, t_list **g_list)
{
	if (*buf != NULL)
		make_node(buf, TOKEN_END, g_list);
	(*line)++;
	if (**line == '<')
	{
		if (make_A_redir_node(buf, line, type, g_list) < 0)
			return (-1);
	}
	else
	{
		if (is_white_space(line, buf, type, g_list) == 0)
			(*line)++;
		if (**line != ' ' && **line != '\t' && **line != '<'
			&& **line != '>' && **line != '|' && **line != '\0')
		{
			while (**line != ' ' && **line != '<' && **line != '>'
				&& **line != '|' && **line != '\0')
				make_string(**line, buf), (*line)++;
			make_node(buf, L_REDIR, g_list), (*line)--;
		}
		else
			return (-1);
	}
	return (0);
}

int	make_H_redir_node(char **buf, char **line, int *type, t_list **g_list)
{
	(*line)++;
	if (is_white_space(line, buf, type, g_list) == 0)
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
		make_node(buf, A_REDIR, g_list);
		(*line)--;
	}
	else
		return (-1);
	return (0);
}

int	make_R_redir_node(char **buf, char **line, int *type, t_list **g_list)
{
	if (*buf != NULL)
		make_node(buf, TOKEN_END, g_list);
	(*line)++;
	if (**line == '>')
	{
		if (make_H_redir_node(buf, line, type, g_list) < 0)
			return (-1);
	}
	else
	{
		if (is_white_space(line, buf, type, g_list) == 0)
			(*line)++;
		if (**line != ' ' && **line != '\t' && **line != '<'
			&& **line != '>' && **line != '|' && **line != '\0')
		{
			while (**line != ' ' && **line != '<' && **line != '>'
				&& **line != '|' && **line != '\0')
				make_string(**line, buf), (*line)++;
			make_node(buf, R_REDIR, g_list), (*line)--;
		}
		else
			return (-1);
	}
	return (0);
}
