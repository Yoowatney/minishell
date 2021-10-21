/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 22:37:49 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/13 22:04:58 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *ptr1, const char *ptr2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (*ptr1 != *ptr2)
			return (*(unsigned char *)ptr1 - *(unsigned char *)ptr2);
		else if (*ptr1 == '\0' || *ptr2 == '\0')
			break ;
		else
		{
			i++;
			ptr1++;
			ptr2++;
		}
	}
	return (0);
}

/*#include <stdio.h>
 *
 *int main(int argc, char *argv[])
 *{
 *    char *str;
 *    char *strr;
 *    
 *    str = "asd";
 *    strr = "as";
 *    int com = ft_strncmp(str, strr, 3);
 *    printf("%s %s %d\n", str, strr, com);
 *    return (0);
 *}*/
