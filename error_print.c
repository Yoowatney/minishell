/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:27:09 by jlim              #+#    #+#             */
/*   Updated: 2021/11/09 21:27:10 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_valid(t_list **cmd_head, char *cmd_table)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(cmd_table, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	no_file_cd(char **cd_cmd, char *check_home)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cd_cmd[0], 2);
	ft_putstr_fd(": ", 2);
	if (cd_cmd[1] && check_home == NULL)
		ft_putstr_fd(cd_cmd[1], 2);
	else if (check_home != NULL)
		ft_putstr_fd(check_home, 2);
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

int	error_exit1(t_list **cmd_head)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": too many arguments\n", 2);
	return (1);
}

int	error_exit2(t_list **cmd_head)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((*cmd_head)->cmd_table[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}
