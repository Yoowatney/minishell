/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:11:24 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 21:11:25 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_cmd_swung(t_list **cmd_head, char **my_envp, t_env **env)
{
	char	*user;
	char	*user_home;

	if (ft_strlen((*cmd_head)->cmd_table[1]) > 1)
	{
		user = ft_strdup(&(*cmd_head)->cmd_table[1][1]);
		if (!user)
			error_check("");
		user_home = check_user(my_envp, user);
		if (!user_home)
		{
			no_file_cd(cmd_head);
			free(user);
			return (1);
		}
		save_oldpwd(env);
		chdir(user_home);
		free(user);
		free(user_home);
	}
	else if (!(check_home(my_envp)))
		return (print_not_home(cmd_head));
	save_oldpwd(env);
	chdir(check_home(my_envp));
	return (0);
}

int	cd_cmd_dot(t_list **cmd_head, t_env **env)
{
	char	*updir;

	if (ft_strcmp((*cmd_head)->cmd_table[1], ".") == 0)
	{
		save_oldpwd(env);
		return (0);
	}
	else if (ft_strcmp((*cmd_head)->cmd_table[1], "..") == 0)
	{
		updir = check_updir();
		if (!updir)
		{
			free(updir);
			return (0);
		}
		save_oldpwd(env);
		chdir(updir);
		free(updir);
		return (0);
	}
	return (1);
}

int	cd_hyphen_slash(t_list **cmd_head, t_env **env, char **my_envp)
{
	char	*oldpwd;

	if (ft_strcmp((*cmd_head)->cmd_table[1], "-") == 0)
	{
		oldpwd = check_oldpwd_value(my_envp);
		save_oldpwd(env);
		chdir(oldpwd);
		return (0);
	}
	else if (ft_strcmp((*cmd_head)->cmd_table[1], "/") == 0)
	{
		save_oldpwd(env);
		chdir("/");
		return (0);
	}
	return (1);
}

int	cd_cmd(t_list **cmd_head, t_env **env)
{
	save_oldpwd(env);
	if (chdir((*cmd_head)->cmd_table[1]) < 0)
	{
		no_file_cd(cmd_head);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_list **cmd_head, char **my_envp, t_env **env)
{
	int		i;

	i = 1;
	if ((*cmd_head)->cmd_table[1])
	{
		if (ft_strncmp((*cmd_head)->cmd_table[1], "~", 1) == 0)
			return (cd_cmd_swung(cmd_head, my_envp, env));
		else if (cd_hyphen_slash(cmd_head, env, my_envp) == 0)
			return (0);
		else if (cd_cmd_dot(cmd_head, env) == 0)
			return (0);
		else
			return (cd_cmd(cmd_head, env));
	}
	else
	{
		if (!(check_home(my_envp)))
			return (print_not_home(cmd_head));
		save_oldpwd(env);
		chdir(check_home(my_envp));
		return (0);
	}
	return (0);
}
