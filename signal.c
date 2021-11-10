/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:16 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 19:07:36 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned int	g_exit_status;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	bin_sig_handler(int signum)
{
	extern const char *const	sys_siglist[];

	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd((char *)(sys_siglist[SIGQUIT]), 2);
		ft_putstr_fd(": 3\n", 2);
		g_exit_status = 131;
	}
}

void	init_execute_bin(void)
{
	signal(SIGINT, bin_sig_handler);
	signal(SIGQUIT, bin_sig_handler);
}
