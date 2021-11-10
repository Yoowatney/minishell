/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse_rewind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:38:40 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/11 03:26:58 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reparse_rewind(t_list **list)
{
	rewind_list(list);
	re_parsing(list);
	rewind_list(list);
}

void	split_cmd(t_list **cmd_head, t_list *list)
{
	*cmd_head = create_list(list);
	split_cmd_node(list, *cmd_head);
	rewind_list(cmd_head);
}

void	split_redir(t_list **redir_head, t_list *list)
{
	*redir_head = create_list(list);
	split_redir_node(list, *redir_head);
	rewind_list(redir_head);
}
