/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:03 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 19:34:15 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	rewind_list(t_list **list)
{
	while (*list && (*list)->prev)
		*list = (*list)->prev;
}

char	**allocate_envp(t_env *env)
{
	char	**ret;
	int		size;
	int		i;

	size = env_size(env);
	i = 0;
	ret = ft_malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		ret[i] = ft_strdup(env->env_line);
		env = env -> next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	error_check(char *str)
{
	if (errno == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (errno != 0 && errno != 4 && errno != 22)
	{
		ft_putstr_fd("error : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
}
