#include "minishell.h"

int	builtin_env(char **my_envp, t_list **cmd_head)
{
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		while (*my_envp)
		{
			ft_putstr_fd(*my_envp, (*cmd_head)->pipe[1]);
			ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
			my_envp++;
			if (*my_envp == NULL)
				break ;
		}
	}
	else
	{
		while (*my_envp)
		{
			ft_putstr_fd(*my_envp, 1);
			ft_putchar_fd('\n', 1);
			my_envp++;
			if (*my_envp == NULL)
				break ;
		}
	}

	return (1);
}