#include "minishell.h"

void	delete_env(t_env *env, char *unset_key)
{
	t_env	*check;
	t_env	*tmp;

	check = env;
	while (check)
	{
		if (ft_strcmp((check)->key, unset_key) == 0)
		{
			printf("%s %s\n", unset_key, (check)->key);
			
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
			
			free((check)->key);
			free((check)->value);
			free((check)->env_line);
			(check)->key = NULL;
			(check)->value = NULL;
			(check)->env_line = NULL;
			(check)->prev = NULL;
			(check)->next = NULL;
			free(check);
			check = tmp;
		}
		if ((check)->next)
			(check) = (check)->next;
		else
			break ;
	}
}

int	builtin_unset(t_list **cmd_head, t_env **env, t_list **g_list)
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

	//(void)cmd_head;
	
	char	*unset_key;
	int		i;

	//(void)unset_key;
	//(void)i;
	
	if ((*cmd_head)->cmd_table[1])
	{
		i = 1;
		while ((*cmd_head)->cmd_table[i])
		{
			unset_key = (*cmd_head)->cmd_table[i];
			delete_env(*env, unset_key);
			if ((*cmd_head)->cmd_table[i+1])
				i++;
			else
				break ;
		}
	}
	else
		return (1);
	return (1);
}