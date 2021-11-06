#include "minishell.h"

char	**export_string(t_env *env)
{
	t_env	*change;
	char	*key;
	char	*value;
	char	*result1;
	char	*result2;
	char	*result3;
	char	**export_str;
	char	**return_value;

	change = env;
	export_str = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!export_str)
		return (NULL);
	return_value = export_str;
	while ((change)->next)
	{
		key = ft_strdup((change)->key);
		value = (change)->value;
		result1 = ft_strjoin(key, "=\"");
		result2 = ft_strjoin(result1, value);
		result3 = ft_strjoin(result2, "\"");
		*export_str = result3;
		export_str++;
		change = (change)->next;
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

int	check_equal_sign(char *cmd_table)
{
	while (*cmd_table)
	{
		if (*cmd_table == '=')
			return (1);
		cmd_table++;
	}
	return (0);
}

t_env	*check_key(t_env *env, char *key)
{
	t_env	*env_key;

	env_key = env;
	while ((env_key)->key)
	{
		if (ft_strcmp((env_key)->key, key) == 0)
			return (env_key);
		if ((env_key)->next)
			(env_key) = (env_key)->next;
		else
			break ;
	}
	return (NULL);
}

void	free_str(char **export_str)
{
	char	*temp;
	int		i;

	i = 0;
	while (export_str[i])
	{
		temp = export_str[i];
		free(temp);
		i++;
	}
	free(export_str);
}

int	builtin_export(t_list **cmd_head, t_env **env, t_list **g_list)
{
	char	**export_str;
	int		size;
	char	**result;
	t_env	*new;
	char	*cmd_table;
	char	*new_key;

	(void)result;

	size = env_size(*env);

	rewind_list(g_list);
	rewind_list(&(*g_list)->cmd_list);
	
	if ((*cmd_head)->cmd_table[1])
	{
		while ((*g_list)->cmd_list)	
		{
			if ((*g_list)->cmd_list->type == PIPE)
				return (1);
			if ((*g_list)->cmd_list->next != NULL)
				(*g_list)->cmd_list = (*g_list)->cmd_list->next;
			else
				break ;
		}
		cmd_table = (*cmd_head)->cmd_table[1];
		if (!check_equal_sign(cmd_table))
			return (0);
		new_key = get_key(cmd_table);
		if ((new = check_key(*env, new_key)))
		{
			free(new->value);
			free(new->env_line);
			new->env_line = ft_strdup(cmd_table);
			new->value = get_value(cmd_table);
		}
		else
		{
			new = malloc(sizeof(t_env));
			error_check("");
			new -> next = NULL;
			new -> prev = NULL;
			new -> env_line = ft_strdup(cmd_table);		
			new -> key = get_key(cmd_table);
			new -> value = get_value(cmd_table);
			env_add_back(env, new);
		}
	}
	else
	{
		char	**temp;

		if (!(export_str = export_string(*env)))
			return (0);
		temp = export_str;
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
		free_str(temp);
	}
	return (1);
}