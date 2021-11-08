#include "minishell.h"

int	builtin_echo(t_list **cmd_head)
{
	char	**print;
	int		n_flag;

	print = (*cmd_head)->cmd_table;
	if (*(print+1))
		print++;
	else
		return (0);
	n_flag = 0;
	if (ft_strcmp(*print, "-n") == 0)
	{
		while (ft_strcmp(*print, "-n") == 0 && *(print+1))
			print++;
		n_flag = 1;
	}
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		while (*print)
		{
			ft_putstr_fd(*print, (*cmd_head)->pipe[1]);
			if (*(print + 1))
				ft_putchar_fd(' ', (*cmd_head)->pipe[1]);
			print++;
			if (*print == NULL)
			{
				if (n_flag == 0)
					ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
				break ;
			}
		}
	}
	else
	{
		while (*print)
		{
			ft_putstr_fd(*print, 1);
			if (*(print + 1))
				ft_putchar_fd(' ', 1);
			print++;
			if (*print == NULL)
			{
				if (n_flag == 0)
					ft_putchar_fd('\n', 1);
				break ;
			}	
		}
	}
	return (0);
}
