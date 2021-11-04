#include "minishell.h"

char	**export_string(t_env **env)
{
	t_env	**change;
	char	*key;
	char	*value;
	char	*result;
	char	**export_str;
	char	**return_value;

	change = env;
	export_str = (char **)malloc(sizeof(char *) * (env_size(*env) + 1));
	if (!export_str)
		return (NULL);
	return_value = export_str;
	while ((*change)->next)
	{
		key = (*change)->key;
		value = (*change)->value;
		result = ft_strjoin(key, "=\"");
		result = ft_strjoin(result, value);
		result = ft_strjoin(result, "\"");
		*export_str = ft_strdup(result);
		export_str++;
		*change = (*change)->next;
	}
	*export_str = NULL;
	return (return_value);
}

char	**sort_list(char **export_str, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (export_str[j + 1] && (ft_strncmp(export_str[j], export_str[j + 1], 
					ft_strlen(export_str[j])) > 0))
			{
				temp = export_str[j];
				export_str[j] = export_str[j + 1];
				export_str[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (NULL);

}

char	*export_key(char **envp)
{
	char	*ret;
	int		i;

	i = 0;
	while (**envp != '=')
	{
		(*envp)++;
	}
	**envp = '\0';
	ret = ft_strdup(*envp);
	**envp = '=';
	return (ret);
}

int	builtin_export(t_list **cmd_head, t_env **env)
{
	char	**export_str;
	int		size;
	char	**result;
	t_env	*new;
	char	*cmd_table;

	(void)result;

	size = env_size(*env);
	
	if ((*cmd_head)->cmd_table[1])
	{
		cmd_table = (*cmd_head)->cmd_table[1];
		printf("export str : %s\n", (*cmd_head)->cmd_table[1]);
		new = malloc(sizeof(t_env));
		//error_check("");
		new -> next = NULL;
		new -> prev = NULL;
		write(1, "ss", 2);
		new -> env_line = ft_strdup((*cmd_head)->cmd_table[1]);
		printf("new : %s\n", new->env_line);
		
		//new -> key = get_key(ft_strdup(cmd_table));
		//new -> value = get_value((*cmd_head)->cmd_table[1]);
		//env_add_back(env, new);
		return (1);
	}
	else
	{
		export_str = export_string(env);
		sort_list(export_str, size);
		if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
		{	
			while (*export_str)
			{
				ft_putstr_fd("declare -x ", (*cmd_head)->pipe[1]);
				ft_putstr_fd(*export_str, (*cmd_head)->pipe[1]);
				ft_putstr_fd("\n", (*cmd_head)->pipe[1]);
				export_str++;
				if (!*export_str)
					break ;
			}
		}
		else
		{
			while (*export_str)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(*export_str, 1);
				ft_putstr_fd("\n", 1);
				export_str++;
				if (!*export_str)
					break ;
			}
		}
	}
	return (1);
}