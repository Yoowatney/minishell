/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:09:44 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 19:36:06 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_home(char **my_envp)
{
	char	**home;
	char	*new;

	home = my_envp;
	while (*home)
	{
		if (ft_strncmp(*home, "HOME", 4) == 0)
		{
			new = ft_strchr(*home, '=');
			if (!new)
				return (NULL);
			new++;
			return (new);
		}	
		home++;
		if (*home == NULL)
			break ;
	}
	return (NULL);
}

char	*check_updir(void)
{
	char	*pwd;
	char	*updir;
	int		i;
	int		check;

	pwd = getcwd(NULL, BUFSIZ);
	i = 0;
	check = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			check = i;
		i++;
	}
	pwd[check] = 0;
	updir = ft_strdup(pwd);
	free(pwd);
	return (updir);
}

int	check_end_slash(char *value)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (value[i])
	{
		if (value[i] == '/')
			check = i;
		i++;
	}
	return (check);
}

char	*check_user(char **my_envp, char *user)
{
	char	*home;
	char	*user_home;
	int		check;

	home = check_home(my_envp);
	if (!home)
		return (NULL);
	check = check_end_slash(home);
	check++;
	user_home = ft_strdup(&home[check]);
	if (ft_strcmp(user_home, user) == 0)
	{
		free(user_home);
		return (ft_strdup(home));
	}
	free(user_home);
	return (NULL);
}

int	print_not_home(char **cd_cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(*cd_cmd, 2);
	ft_putstr_fd(": HOME not set\n", 2);
	return (1);
}
