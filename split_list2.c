/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:15:46 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 16:15:46 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choice_condition(int type)
{
	if (type == L_REDIR || type == R_REDIR || type == A_REDIR
		|| type == HEREDOC)
	{
		return (1);
	}
	else if (type == CRITERIA)
	{
		return (0);
	}
	return (-1);
}

void	init_redir_node(char ***redir_table, int **redir_type_table)
{
	*redir_table = NULL;
	*redir_type_table = NULL;
}
