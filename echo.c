#include "minishell.h"

int	builtin_echo(t_list **cmd_head)
{
	char	**print;

	print = (*cmd_head)->cmd_table;
	print++;
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		
		while (*print)
		{
			ft_putstr_fd(*print, (*cmd_head)->pipe[1]);
			ft_putchar_fd(' ', (*cmd_head)->pipe[1]);
			print++;
			if (*print == NULL)
				break ;
		}

	}
	else
	{
		while (*print)
		{
			ft_putstr_fd(*print, 1);
			ft_putchar_fd(' ', 1);
			print++;
			if (*print == NULL)
				break ;
		}
	}
	return (1);
}