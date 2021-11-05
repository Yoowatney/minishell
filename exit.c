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

void	all_free(t_list **g_list, char **cmdline)
{
	rewind_list(g_list);
	rewind_list(&((*g_list)->cmd_list));
	rewind_list(&((*g_list)->redir_list));
	
	ft_lstclear(&((*g_list)->cmd_list));
	ft_lstclear(&((*g_list)->redir_list));	
	(*g_list)->cmd_list = NULL;
	(*g_list)->redir_list = NULL;
	ft_lstclear(g_list);
	(*g_list) = NULL;
	

	
	free(*cmdline);
}


int	builtin_exit(t_list **g_list, char **cmdline, t_env **env)
{
	rewind_list(g_list);
	rewind_list(&(*g_list)->cmd_list);
	while ((*g_list)->cmd_list)
	{
		if ((*g_list)->cmd_list->type == PIPE)
		{
			all_free(g_list, cmdline);
			exit (1); 
		}	
		if ((*g_list)->cmd_list->next != NULL)
			(*g_list)->cmd_list = (*g_list)->cmd_list->next;
		else
			break ;
	}
	all_free(g_list, cmdline);
	(void)env;
	//rewind_env(env);
	//ft_envclear(env);
	exit(2);
}