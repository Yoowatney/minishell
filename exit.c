#include "minishell.h"

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


int	builtin_exit(t_list **g_list, char **cmdline)
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
	exit(2);
}