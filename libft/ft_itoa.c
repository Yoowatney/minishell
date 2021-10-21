/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:09:50 by yoyoo             #+#    #+#             */
/*   Updated: 2021/08/24 23:37:50 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	int_len(int n)
{
	int	cnt;
	int	fix;

	fix = n;
	cnt = 0;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	if (fix >= 0)
		return (cnt + 1);
	else
		return (cnt + 2);
}

static	void	fill_ret(char *ret, int n, int size)
{
	while (n)
	{
		ret[size - 1] = n % 10 + 48;
		n /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		size;

	size = int_len(n);
	if (n > 0)
	{
		ret = (char *)malloc(sizeof(char) * (size));
		if (!ret)
			return (0);
	}
	else if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
	{
		ret = (char *)malloc(sizeof(char) * (size));
		if (!ret)
			return (0);
		ret[0] = '-';
		n *= -1;
	}
	ret[size-- - 1] = '\0';
	fill_ret(ret, n, size);
	return (ret);
}
