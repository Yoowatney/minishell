/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:34:47 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 15:34:49 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_list **cmd_head)
{
	char	*pwd;

	pwd = getcwd(NULL, BUFSIZ);
	if (!pwd)
		return (1);
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		ft_putstr_fd(pwd, (*cmd_head)->pipe[1]);
		ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
	}
	free(pwd);
	return (0);
}
