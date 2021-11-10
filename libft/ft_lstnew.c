/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:19:06 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 16:23:55 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *buf)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (!ret)
	{
		ft_putstr_fd("malloc error\n", 1), exit(errno);
	}
	ret->cmd_table = malloc(sizeof(char *) * 2);
	ret->cmd_table[0] = buf;
	ret->cmd_table[1] = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	ret->type = 0;
	ret->length = 0;
	ret->exit_status = 0;
	ret->file_type_table = NULL;
	ret->infile = 0;
	ret->outfile = 0;
	ret->redir_list = NULL;
	ret->cmd_list = NULL;
	ret->cmdline = NULL;
	return (ret);
}
