/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:16 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 01:46:30 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	bin_sig_handler(int signum)
{
	extern const char *const	sys_siglist[];

	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd((char *)(sys_siglist[SIGQUIT]), 2);
		ft_putstr_fd(": 3\n", 2);
	}
}

void	init_execute_bin(void)
{
	signal(SIGINT, bin_sig_handler);
	signal(SIGQUIT, bin_sig_handler);
}
