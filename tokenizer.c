/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:07 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 16:14:19 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token2(char **line, char **buf, t_env **env)
{
	int	error_num;

	error_num = -2;
	if (**line == '\"')
		error_num = open_double_quote(line, buf, env);
	else if (**line == '\'')
		error_num = open_single_quote(line, buf);
	else if (**line == ';' || **line == '\\')
		error_num = -1;
	else if (**line == '$')
		error_num = is_dollar(line, buf, env);
	return (error_num);
}

int	check_token1(char **line, char **buf, int *type, t_list **g_list)
{
	int	error_num;

	error_num = -2;
	if (**line == ' ')
		error_num = is_white_space(line, buf, type, g_list);
	else if (**line == '|')
		error_num = make_pipe_node(buf, line, type, g_list);
	else if (**line == '<')
		error_num = make_L_redir_node(buf, line, type, g_list);
	else if (**line == '>')
		error_num = make_R_redir_node(buf, line, type, g_list);
	else
		error_num = make_string(**line, buf);
	return (error_num);
}

int	tokenizer(char *line, t_env **env, t_list **g_list)
{
	int			error_num;
	static char	*buf;
	int			type;

	buf = NULL;
	type = TOKEN_END;
	while (*line)
	{
		error_num = check_token2(&line, &buf, env);
		if (error_num == -2)
			error_num = check_token1(&line, &buf, &type, g_list);
		if (error_num < 0)
		{
			free(buf), buf = NULL;
			return (-1);
		}
		line++;
	}
	if (*g_list && (ft_lstlast(*g_list)->type == TOKEN_END
			|| ft_lstlast(*g_list)->type == PIPE) && type != PIPE)
		add_arg(&buf, *g_list);
	make_node(&buf, type, g_list);
	return (error_num);
}
