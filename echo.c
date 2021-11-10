/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:30:05 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 17:30:06 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_util(t_list **cmd_head, char **print, int n_flag)
{
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		while (*print)
		{
			if (**print == '\0' && *(print + 1))
				print++;
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
		if (**print == '\0' && *(print + 1))
			print++;
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

int	builtin_echo(t_list **cmd_head)
{
	char	**print;
	int		n_flag;

	print = (*cmd_head)->cmd_table;
	if (*(print + 1))
		print++;
	else
		return (0);
	n_flag = 0;
	if (ft_strcmp(*print, "-n") == 0)
	{
		while (ft_strcmp(*print, "-n") == 0 && *(print + 1))
			print++;
		if (ft_strcmp(*print, "-n") == 0)
			return (0);
		n_flag = 1;
	}
	if (echo_util(cmd_head, print, n_flag) == 1)
		return (0);
	else
		echo_util2(print, n_flag);
	return (0);
}
