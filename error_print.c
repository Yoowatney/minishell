#include "minishell.h"

void	print_valid(t_list **cmd_head, char *cmd_table)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(cmd_table, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	no_file_cd(t_list **cmd_head)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	no_file_env(t_list **cmd_head, char *cmd_table)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd_table, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_exit1(t_list **cmd_head)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": too many arguments\n", 2);
}

void	error_exit2(t_list **cmd_head)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}
