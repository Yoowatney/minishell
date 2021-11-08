#include "minishell.h"

int	check_env_cmd(t_list **cmd_head)
{
	char	**cmd_table;
	int		i;
	char	*error_msg = "NO such file or directory\n";

	cmd_table = (*cmd_head)->cmd_table;
	i = 1;
	while (cmd_table[i])
	{
		if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
		{
			if (check_equal_sign(cmd_table[i]) == -1)
			{	
				ft_putstr_fd(error_msg, 2);
				return (-1);
			}
		}
		else
		{
			if (check_equal_sign(cmd_table[i]) == -1)
			{	
				ft_putstr_fd(error_msg, 2);
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

int	extra_cmd(t_list **cmd_head)
{
	char	**cmd_table;
	int		i;

	cmd_table = (*cmd_head)->cmd_table;
	i = 1;
	while (cmd_table[i])
	{
		if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
		{
			ft_putstr_fd(cmd_table[i], (*cmd_head)->pipe[1]);
			ft_putchar_fd('\n', (*cmd_head)->pipe[1]);
		}
		else
		{
			ft_putstr_fd(cmd_table[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (1);
}

int	builtin_env(char **my_envp, t_list **cmd_head)
{
	if (check_env_cmd(cmd_head) == -1)
		return (-1);
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
		if ((*cmd_head)->cmd_table[1])
		{
			extra_cmd(cmd_head);
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
		if ((*cmd_head)->cmd_table[1])
		{
			extra_cmd(cmd_head);
		}
	}

	return (1);
}