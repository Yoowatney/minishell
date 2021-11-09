/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse_rewind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:38:40 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/09 15:59:24 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reparse_rewind(t_list **g_list)
{
	rewind_list(g_list);
	re_parsing(g_list);
	rewind_list(g_list);
}

void	split_cmd(t_list **cmd_head, t_list *g_list)
{
	*cmd_head = create_list(g_list);
	split_cmd_node(g_list, *cmd_head);
	rewind_list(cmd_head);
}

void	split_redir(t_list **redir_head, t_list *g_list)
{
	*redir_head = create_list(g_list);
	split_redir_node(g_list, *redir_head);
	rewind_list(redir_head);
}
