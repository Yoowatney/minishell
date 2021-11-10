#include "minishell.h"

int	echo_util(t_list **cmd_head, char **print, int n_flag)
{
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{
		while (*print)
		{
			if (**print == '\0' && *(print + 1))
				print++;
			if (**print == '\0' && !*(print + 1))
				return (1);
			ft_putstr_fd(*print, (*cmd_head)->pipe[1]);
			if (*(print + 1) && **print != '\0')
				ft_putchar_fd(' ', (*cmd_head)->pipe[1]);
			print++;
			if (*print == NULL)
			{
				if (n_flag == 0)
					ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
				break ;
			}
		}
		return (1);
	}
	return (0);
}

void	echo_util2(char **print, int n_flag)
{
	while (*print)
	{
		if (**print == '\0' && *(print + 1))
			print++;
		if (**print == '\0' && !(*(print + 1)))
			return ;
		ft_putstr_fd(*print, 1);
		if (*(print + 1) && **print != '\0')
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
