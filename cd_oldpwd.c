/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:10:04 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 19:52:58 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_oldpwd_value(char **my_envp)
{
	char	**oldpwd;
	char	*ret;

	oldpwd = my_envp;
	while (*oldpwd)
	{
		if (ft_strncmp(*oldpwd, "OLDPWD", 6) == 0)
		{
			ret = ft_strchr(*oldpwd, '=');
			if (!ret)
				return (NULL);
			ret++;
			return (ret);
		}
		oldpwd++;
		if (*oldpwd == NULL)
			break ;
	}
	return (NULL);
}

t_env	*check_oldpwd(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
			break ;
		if (tmp->next)
			tmp = tmp->next;
		else
			return (NULL);
	}
	return (tmp);
}

void	save_oldpwd_util(t_env **tmp, t_env **oldpwd)
{
	if ((*tmp)->prev && (*tmp)->next)
	{
		(*tmp)->prev->next = (*oldpwd);
		(*tmp)->next->prev = (*oldpwd);
		(*oldpwd)->next = (*tmp)->next;
		(*oldpwd)->prev = (*tmp)->prev;
	}
	else if ((*tmp)->prev)
	{
		(*tmp)->prev->next = (*oldpwd);
		(*oldpwd)->next = NULL;
		(*oldpwd)->prev = (*tmp)->prev;
	}
	else
	{
		(*tmp)->next->prev = (*oldpwd);
		(*oldpwd)->next = (*tmp)->next;
		(*oldpwd)->prev = (*tmp)->prev;
	}
}

void	save_oldpwd(t_env **env)
{
	char	*pwd;
	t_env	*oldpwd;
	t_env	*tmp;

	pwd = getcwd(NULL, BUFSIZ);
	oldpwd = ft_malloc(sizeof(t_env));
	tmp = check_oldpwd(env);
	if (tmp == NULL)
	{
		free(pwd);
		free(oldpwd);
		return ;
	}
	oldpwd->env_line = ft_strjoin(ft_strdup("OLDPWD="), pwd);
	oldpwd->key = ft_strdup("OLDPWD");
	oldpwd->value = pwd;
	save_oldpwd_util(&tmp, &oldpwd);
	free((tmp)->env_line);
	free((tmp)->key);
	free((tmp)->value);
	free(tmp);
}
