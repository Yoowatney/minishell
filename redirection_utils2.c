/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:15:37 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 19:52:38 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_L_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		ft_dup2(copy[0], STDIN_FILENO);
		ft_close(fd);
	}
}

void	close_R_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		ft_dup2(copy[1], STDOUT_FILENO);
		ft_close(fd);
	}
}
