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

char	*check_user(char **my_envp, char *user)
{
	char	*home;
	char	*user_home;
	int		i;
	int		check;

	i = 0;
	check = 0;
	home = check_home(my_envp);
	if (!home)
		return (NULL);
	while (home[i])
	{
		if (home[i] == '/')
			check = i;
		i++;
	}
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

char	*check_oldpwd(char **my_envp)
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

int	builtin_cd(t_list **g_list, t_list **cmd_head, char **my_envp)
{
	rewind_list(g_list);
	rewind_list(&(*g_list)->cmd_list);
	int		i;
	char	*user;
	char	*error_msg_home = "HOME not set\n";
	char	*user_home;
	char	*oldpwd;
	
	i = 1;
	if ((*cmd_head)->cmd_table[1])
	{
		if (chdir((*cmd_head)->cmd_table[1]) == 0)
			return (1);
		else if (ft_strcmp((*cmd_head)->cmd_table[1], "-") == 0)
		{
			oldpwd = check_oldpwd(my_envp);
			chdir(oldpwd);
			return (1);
		}
		else if (ft_strncmp((*cmd_head)->cmd_table[1], "~", 1) == 0)
		{
			if (ft_strlen((*cmd_head)->cmd_table[1]) > 1)
			{
				user = ft_strdup(&(*cmd_head)->cmd_table[1][i]);
				if (!user)
				{
					ft_putstr_fd(strerror(errno), 2);
					return (-1);
				}
				user_home = check_user(my_envp, user);
				if (!user_home)
				{
					ft_putstr_fd(strerror(errno), 2);
					free(user);
					return (-1);
				}
				chdir(user_home);
				free(user);
				free(user_home);
				return (1);
			}
			else if (!(check_home(my_envp)))
			{
				write(2, error_msg_home, 13);
				return (0);
			}
			chdir(check_home(my_envp));
			return (1);
		}
		else if (ft_strcmp((*cmd_head)->cmd_table[1], "/") == 0)
		{
			chdir("/");
			return (1);
		}
		else if (ft_strcmp((*cmd_head)->cmd_table[1], ".") == 0)
			return (1);
		else if (ft_strcmp((*cmd_head)->cmd_table[1], "..") == 0)
		{
			char	*updir;
			
			updir = check_updir();
			if (!updir)
			{
				free(updir);
				return (0);
			}
			chdir(updir);
			free(updir);
			return (1);
		}
		else
		{
			ft_putstr_fd(strerror(errno), 2);
		}
	}
	else
	{
		if (!(check_home(my_envp)))
		{
			write(2, error_msg_home, 13);
			return (0);
		}
		chdir(check_home(my_envp));
		return (1);
	}
	return (0);
}
