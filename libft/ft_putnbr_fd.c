/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:50:58 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:34:06 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	rec(int nb, int fd)
{
	char	c;

	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	c = '0' + nb % 10;
	if (nb == 0)
		return ;
	rec(nb / 10, fd);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == 0)
		write(fd, "0", 1);
	else if (nb == -2147483648)
	{
		rec(nb / 10, fd);
		write(fd, "8", 1);
	}
	else
		rec(nb, fd);
}
