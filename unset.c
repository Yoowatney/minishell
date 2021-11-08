#include "minishell.h"

void	free_env(t_env **check, t_env **tmp)
{
	free((*check)->key);
	free((*check)->value);
	free((*check)->env_line);
	(*check)->key = NULL;
	(*check)->value = NULL;
	(*check)->env_line = NULL;
	(*check)->prev = NULL;
	(*check)->next = NULL;
	free(*check);
	*check = *tmp;
}

void	delete_env(t_env *env, char *unset_key)
{
	t_env	*check;
	t_env	*tmp;

	check = env;
	while (check)
	{
		if (ft_strcmp((check)->key, unset_key) == 0)
		{			
			if ((check)->prev && (check)->next)
			{
				(check)->prev->next = (check)->next;
				(check)->next->prev = (check)->prev;
				tmp = check->next;
			}
			else if ((check)->prev)
			{
				(check)->prev->next = NULL;
				tmp = check->prev;
			}	
			else
			{
				(check)->next->prev = NULL;
				tmp = check->next;
			}
			free_env(&check, &tmp);
		}
		if ((check)->next)
			(check) = (check)->next;
		else
			break ;
	}
}

int	check_unset_alpha(char *cmd_table)
{
	int	i;
	
	i = 0;
	while (cmd_table[i])
	{
		if ((cmd_table[i] >= 65 && cmd_table[i] <= 90)
		|| (cmd_table[i] >= 97 && cmd_table[i] <= 122)
		|| (cmd_table[i] >= 48 && cmd_table[i] <= 57))
		{
			i++;
			continue ;
		}
		if (cmd_table[i])
			return (-1);
	}
	return (1);
}

int	builtin_unset(t_list **cmd_head, t_env **env)
{
	char	*unset_key;
	int		i;
	char	*cmd_table;
	int		ret;
	
	i = 1;
	ret = 0;
	if ((*cmd_head)->cmd_table[i])
	{
		while ((*cmd_head)->cmd_table[i])
		{
			cmd_table = (*cmd_head)->cmd_table[i];
			if (check_num(cmd_table) == -1
				|| check_unset_alpha(cmd_table) == -1)
			{
				print_valid(cmd_head, cmd_table);
				ret = 1;
				if ((*cmd_head)->cmd_table[i+1])
					i++;
				else
					break ;
				continue ;
			}
			unset_key = (*cmd_head)->cmd_table[i];
			delete_env(*env, unset_key);
			if ((*cmd_head)->cmd_table[i+1])
				i++;
			else
				break ;
		}
	}
	return (ret);
}