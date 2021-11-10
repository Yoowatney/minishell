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

int	cd_cmd_swung(char **cd_cmd, char **my_envp, t_env **env)
{
	char	*user;
	char	*user_home;

	if (ft_strlen(cd_cmd[1]) > 1)
	{
		user = ft_strdup(&(cd_cmd[1][1]));
		user_home = check_user(my_envp, user);
		if (!user_home)
		{
			no_file_cd(cd_cmd, NULL);
			free(user);
			return (1);
		}
		save_oldpwd(env);
		ft_chdir(user_home);
		free(user);
		free(user_home);
	}
	else if (!(check_home(my_envp)))
		return (print_not_home(cd_cmd));
	save_oldpwd(env);
	if (chdir(check_home(my_envp)) < 0)
		no_file_cd(cd_cmd, check_home(my_envp));
	return (0);
}

int	cd_cmd_dot(char **cd_cmd, t_env **env)
{
	char	*updir;

	if (ft_strcmp(cd_cmd[1], ".") == 0)
	{
		save_oldpwd(env);
		return (0);
	}
	else if (ft_strcmp(cd_cmd[1], "..") == 0)
	{
		updir = check_updir();
		if (!updir)
		{
			free(updir);
			return (0);
		}
		save_oldpwd(env);
		ft_chdir(updir);
		free(updir);
		return (0);
	}
	return (1);
}

int	cd_hyphen_slash(char **cd_cmd, t_env **env, char **my_envp)
{
	char	*oldpwd;

	if (ft_strcmp(cd_cmd[1], "-") == 0)
	{
		oldpwd = check_oldpwd_value(my_envp);
		if (oldpwd == NULL)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			return (1);
		}
		save_oldpwd(env);
		chdir(oldpwd);
		return (0);
	}
	else if (ft_strcmp(cd_cmd[1], "/") == 0)
	{
		save_oldpwd(env);
		ft_chdir("/");
		return (0);
	}
	return (-1);
}

int	cd_path(char **cd_cmd, t_env **env)
{
	save_oldpwd(env);
	if (chdir(cd_cmd[1]) < 0)
	{
		no_file_cd(cd_cmd, NULL);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_list **cmd_head, char **my_envp, t_env **env)
{
	int		i;
	char	**cd_cmd;
	int		ret;

	cd_cmd = delete_null(cmd_head);
	if (cd_cmd[1])
	{
		i = cd_hyphen_slash(cd_cmd, env, my_envp);
		if (i == 0)
			ret = i;
		else if (i == 1)
			ret = i;
		else if (ft_strncmp(cd_cmd[1], "~", 1) == 0)
			ret = cd_cmd_swung(cd_cmd, my_envp, env);
		else if (cd_cmd_dot(cd_cmd, env) == 0)
			ret = 0;
		else
			ret = cd_path(cd_cmd, env);
	}
	else
		ret = only_cd(cd_cmd, my_envp, env);
	free_cmd_table(cd_cmd);
	return (ret);
}
