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
	while (1)
	{
		key = ft_strdup((change)->key);
		value = (change)->value;
		result1 = ft_strjoin(key, "=\"");
		result2 = ft_strjoin(result1, value);
		result3 = ft_strjoin(result2, "\"");
		*export_str = result3;
		export_str++;
		if (change->next)
			change = (change)->next;
		else
			break ;
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

int	check_plus_equal(char *cmd_table)
{
	int	i;

	i = 0;
	if (cmd_table[i] == '+' || cmd_table[i] == '=')
		return (-1);
	i++;
	while (cmd_table[i])
	{
		if (cmd_table[i+1])
		{	
			if (cmd_table[i] == '+' && cmd_table[i+1] == '+')
				return (-1); //not a valid identifier
			else if (cmd_table[i] == '+' && cmd_table[i+1] == '=')
				return (i);
		}
		if (cmd_table[i+1])
			i++;
		else
			break ;
	}
	return (0);
}

int	check_equal_sign(char *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i])
	{
		if (cmd_table[i] == '=')
			return (i);
		i++;
	}
	return (-1);
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

char	*get_export_key(char *cmd_table)
{
	char	*ret;
	int		index;

	index = check_plus_equal(cmd_table);
	if (index >= 1)
	{
		cmd_table[index] = '\0';
		ret = ft_strdup(cmd_table);
		cmd_table[index] = '+';
	}
	else if (index == -1)
		return (NULL);
	else
	{
		index = check_equal_sign(cmd_table);
		if (index == -1)
			return (NULL);
		else
		{
			cmd_table[index] = '\0';
			ret = ft_strdup(cmd_table);
			cmd_table[index] = '=';
		}
	}
	return (ret);
}

char	*get_export_value(char *cmd_table)
{
	char	*ret;
	int		index;

	index = check_plus_equal(cmd_table);
	if (index >= 1)
	{
		index += 2;
		ret = ft_strdup(&cmd_table[index]);
	}
	else if (index == -1)
		return (NULL);
	else
	{
		index = check_equal_sign(cmd_table);
		if (index == -1)
			return (NULL);
		else
		{
			index++;
			ret = ft_strdup(&cmd_table[index]);
		}
	}
	return (ret);
}

int	check_num(char *cmd_table)
{
	if (cmd_table[0] >= 48 && cmd_table[0] <= 57)
		return (-1);
	if (cmd_table[0] == '=')
		return (-1);
	return (1);
}

int	check_alpha(char *cmd_table)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (1)
	{
		if ((cmd_table[i] >= 65 && cmd_table[i] <= 90)
		|| (cmd_table[i] >= 97 && cmd_table[i] <= 122)
		|| (cmd_table[i] >= 48 && cmd_table[i] <= 57))
		{
			i++;
			continue ;
		}
		if (cmd_table[i+1] && cmd_table[i+1] == '='
				&& cmd_table[i] == '+')
			return (1);
		else if (cmd_table[i] && cmd_table[i] == '=')
			return (1);
		else if (!cmd_table[i])
			return (1);
		else if (cmd_table[i])
			return (-1);
	}
	return (1);
}

int	check_identifier(char *cmd_table)
{
	if (check_num(cmd_table) == -1
		|| check_alpha(cmd_table) == -1)
		return (-1); //not a valid identifier
	return (1);
}

int	builtin_export(t_list **cmd_head, t_env **env)
{
	char	**export_str;
	int		size;
	t_env	*new;
	char	*cmd_table;
	char	*new_key;
	char	*tmp;
	char	*value;
	int		ret;


	size = env_size(*env);
	int	i = 1;
	ret = 0;
	if ((*cmd_head)->cmd_table[i])
	{
		while ((*cmd_head)->cmd_table[i])
		{		
			cmd_table = (*cmd_head)->cmd_table[i];
			if (check_identifier(cmd_table) == -1)
			{
				print_valid(cmd_head, cmd_table);
				ret = 1;
				if ((*cmd_head)->cmd_table[i+1])
					i++;
				else
					break ;
				continue ;
			}	
			if (check_equal_sign(cmd_table) == -1)
			{
				if ((*cmd_head)->cmd_table[i+1])
					i++;
				else
					break ;
				continue ;
			}
			new_key = get_export_key(cmd_table);
			if ((new = check_key(*env, new_key))
				&& check_plus_equal(cmd_table) >= 1)
			{
				free(new->env_line);
				value = get_export_value(cmd_table);
				new->value = ft_strjoin(new->value, value);
				tmp = ft_strjoin_ch(ft_strdup(new_key), '=');
				new->env_line = ft_strjoin(tmp, (new->value));
				free(value);
			}
			else if ((new = check_key(*env, new_key)))
			{
				free(new->value);
				free(new->env_line);
				new->value = get_export_value(cmd_table);
				new->env_line = ft_strdup(cmd_table);
			}
			else
			{
				new = malloc(sizeof(t_env));
				error_check("");
				new->next = NULL;
				new->prev = NULL;
				new->key = get_export_key(cmd_table);
				new->value = get_export_value(cmd_table);
				tmp = ft_strjoin_ch(ft_strdup(new_key), '=');
				new->env_line = ft_strjoin(tmp, new->value);
				env_add_back(env, new);
			}
			free(new_key);
			if ((*cmd_head)->cmd_table[i+1])
				i++;
			else
				break ;
		}
	}
	else
	{
		char	**temp;

		if (!(export_str = export_string(*env)))
		{
			ft_putstr_fd("malloc error\n", 2);
			return (1);
		}
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
	return (ret);
}