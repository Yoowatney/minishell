/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:09:59 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/09 15:14:18 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *envp)
{
	char	*ret;
	int		i;

	i = 0;
	while (envp[i] != '=')
	{
		i++;
	}
	envp[i] = '\0';
	ret = ft_strdup(envp);
	envp[i] = '=';
	return (ret);
}

char	*get_value(char	*envp)
{
	char	*ret;

	while (*envp != '=')
		envp++;
	envp++;
	ret = ft_strdup(envp);
	return (ret);
}

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	env_size(t_env *env)
{
	int	cnt;

	cnt = 1;
	if (!env)
		return (0);
	while (env->next != NULL)
	{
		cnt++;
		env = env -> next;
	}
	return (cnt);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*ptr;

	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	ptr = env_last(*env);
	ptr->next = new;
	new->prev = ptr;
}
