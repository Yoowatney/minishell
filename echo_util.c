/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:17:15 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 20:17:16 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_util(t_list **cmd_head, char **print, int n_flag)
{
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		while (*print)
		{
			ft_putstr_fd(*print, (*cmd_head)->pipe[1]);
			if (*(print + 1))
				ft_putchar_fd(' ', (*cmd_head)->pipe[1]);
			print++;
			if (*print == NULL)
			{
				if (n_flag == 0)
					ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
				break ;
			}
		}
		return (1);
	}
	return (0);
}

void	echo_util2(char **print, int n_flag)
{
	while (*print)
	{
		ft_putstr_fd(*print, 1);
		if (*(print + 1))
			ft_putchar_fd(' ', 1);
		print++;
		if (*print == NULL)
		{
			if (n_flag == 0)
				ft_putchar_fd('\n', 1);
			break ;
		}
	}
}
