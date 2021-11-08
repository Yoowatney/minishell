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
	return (updir);
}

int	builtin_cd(t_list **g_list, t_list **cmd_head, char **my_envp)
{
	rewind_list(g_list);
	rewind_list(&(*g_list)->cmd_list);
	while ((*g_list)->cmd_list)
	{
		if ((*g_list)->cmd_list->type == PIPE)
			return (1);
		if ((*g_list)->cmd_list->next != NULL)
			(*g_list)->cmd_list = (*g_list)->cmd_list->next;
		else
			break ;
	}
	char	*pwd;

	pwd = getcwd(NULL, BUFSIZ);
	if ((*cmd_head)->cmd_table[1])
	{
		if (chdir((*cmd_head)->cmd_table[1]) == 0)
			return (1);
		else if (ft_strcmp((*cmd_head)->cmd_table[1], "~") == 0)
		{
			if (!(check_home(my_envp)))
				return (0);
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
	}
	else
	{
		if (!(check_home(my_envp)))
			return (0);
		chdir(check_home(my_envp));
		return (1);
	}
	return (0);
}
