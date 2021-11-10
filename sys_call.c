/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:03:04 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 20:16:37 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		error_check("");
	return (ret);
}

void	ft_dup2(int old, int new)
{
	if (dup2(old, new) < 0)
		error_check("");
}

int	ft_dup(int fd)
{
	int	i;

	i = dup(fd);
	if (i < 0)
		error_check("");
	return (i);
}

void	ft_close(int fd)
{
	if (close(fd) < 0)
		error_check("");
}

void	ft_chdir(char *dir)
{
	if (chdir(dir) < 0)
		error_check("");
}
