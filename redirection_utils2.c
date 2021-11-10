/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:15:37 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 16:15:38 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_L_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		close(fd);
		ft_dup2(copy[0], STDIN_FILENO);
	}
}

void	close_R_fd(int fd, int copy[])
{
	if (fd != 0)
	{
		close(fd);
		ft_dup2(copy[1], STDOUT_FILENO);
	}
}
