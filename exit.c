#include "minishell.h"

void	rewind_env(t_env **env)
{
	while ((*env)->prev)
		(*env) = (*env)->prev;
}

void	ft_envclear(t_env **env)
{
	t_env	*ptr;

	if (!*env)
		return ;
	while (*env != NULL)
	{
		ptr = *env;
		if (ptr)
		{
			free(ptr->env_line);
			ptr->env_line = NULL;
			free(ptr->key);
			ptr->key = NULL;
			free(ptr->value);
			ptr->value = NULL;
			
		}
		if ((*env)->next)
			*env = (*env)->next;
		else
			break ;
		free(ptr);
		ptr = NULL;
	}
	if (*env)
	{
		free((*env)->env_line);
		(*env)->env_line = NULL;
		free((*env)->key);
		(*env)->key = NULL;
		free((*env)->value);
		(*env)->value = NULL;
		free(*env);
		*env = NULL;
	}
}

void	all_free(t_list **g_list)
{
	rewind_list(g_list);
	rewind_list(&((*g_list)->cmd_list));
	rewind_list(&((*g_list)->redir_list));
	
	ft_lstclear(&((*g_list)->cmd_list));
	ft_lstclear(&((*g_list)->redir_list));	
	free((*g_list)->cmdline);
	(*g_list)->cmd_list = NULL;
	(*g_list)->redir_list = NULL;
	ft_lstclear(g_list);
	(*g_list) = NULL;
}

int	check_exit_num(char *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i])
	{
		if (cmd_table[i] >= 48 && cmd_table[i] <= 57)
			i++;
		else
			return (-1);
	}
	return (1);
}

int	builtin_exit(t_list **g_list, t_env **env, t_list **cmd_head)
{
	unsigned char	exit_status;

	exit_status = 0;
	if ((*cmd_head)->cmd_table[1])
	{
		if (check_exit_num((*cmd_head)->cmd_table[1]) == -1)
		{
			exit_status = 255;
		}
		else
			exit_status = (unsigned char)(ft_atoi((*cmd_head)->cmd_table[1]));
	}
	if ((*cmd_head)->cmd_table[1] && (*cmd_head)->cmd_table[2])
	{
		if (check_exit_num((*cmd_head)->cmd_table[1]) == 1)
		{
			printf("too many argument\n");
			return (-1); //too_many_argument;
		}
		else
		{
			printf("numeric argument required\n");
		}
		
	}
	
	rewind_list(g_list);
	rewind_list(&(*g_list)->cmd_list);
	
	all_free(g_list);
	rewind_env(env);
	ft_envclear(env);
	exit(exit_status);
}
