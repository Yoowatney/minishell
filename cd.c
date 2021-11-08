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
	if (!user_home)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (NULL);
	}
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

void	save_oldpwd(t_env **env)
{
	char	*pwd;
	t_env	*oldpwd;
	t_env	*tmp;

	pwd = getcwd(NULL, BUFSIZ);
	oldpwd = malloc(sizeof(t_env));
	if (oldpwd == NULL)
		error_check("");
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp((tmp)->key, "OLDPWD", 6) == 0)
			break ;
		if ((tmp)->next)
			tmp = (tmp)->next;
		else
			return ;
	}
	oldpwd->env_line = ft_strjoin(ft_strdup("OLDPWD="), pwd);
	oldpwd->key = ft_strdup("OLDPWD");
	oldpwd->value = pwd;
	(tmp)->prev->next = oldpwd;
	(tmp)->next->prev = oldpwd;
	oldpwd->next = (tmp)->next;
	oldpwd->prev = (tmp)->prev;
	free((tmp)->env_line);
	free((tmp)->key);
	free((tmp)->value);
	free(tmp);
}

int	builtin_cd(t_list **g_list, t_list **cmd_head, char **my_envp, t_env **env)
{
	rewind_list(g_list);
	rewind_list(&(*g_list)->cmd_list);
	int		i;
	char	*user;
	char	*user_home;
	char	*oldpwd;
	
	i = 1;
	if ((*cmd_head)->cmd_table[1])
	{
		if (ft_strcmp((*cmd_head)->cmd_table[1], "-") == 0)
		{
			oldpwd = check_oldpwd(my_envp);
			save_oldpwd(env);
			chdir(oldpwd);
			return (0);
		}
		else if (ft_strncmp((*cmd_head)->cmd_table[1], "~", 1) == 0)
		{
			if (ft_strlen((*cmd_head)->cmd_table[1]) > 1)
			{
				user = ft_strdup(&(*cmd_head)->cmd_table[1][i]);
				if (!user)
				{
					ft_putstr_fd("malloc error\n", 2);
					return (1);
				}
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
				return (0);
			}
			else if (!(check_home(my_envp)))
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
				ft_putstr_fd(": HOME not set\n", 2);
				return (1);
			}
			save_oldpwd(env);
			chdir(check_home(my_envp));
			return (0);
		}
		else if (ft_strcmp((*cmd_head)->cmd_table[1], "/") == 0)
		{
			save_oldpwd(env);
			chdir("/");
			return (0);
		}
		else if (ft_strcmp((*cmd_head)->cmd_table[1], ".") == 0)
		{
			save_oldpwd(env);
			return (0);
		}
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
			save_oldpwd(env);
			free(updir);
			return (0);
		}
		else if ((*cmd_head)->cmd_table[1])
		{
			save_oldpwd(env);
			if (chdir((*cmd_head)->cmd_table[1]) < 0)
			{
				no_file_cd(cmd_head);
				return (1);
			}
			return (0);
		}
	}
	else
	{
		if (!(check_home(my_envp)))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
			ft_putstr_fd(": HOME not set\n", 2);
			return (1);
		}
		chdir(check_home(my_envp));
		return (0);
	}
	return (0);
}
