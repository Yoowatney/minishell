/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:53:02 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 18:53:02 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmdline_start(char **cmdline)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	*cmdline = readline("bash> ");
	if (*cmdline == NULL)
	{
		ft_putstr_fd("\x1b[1A", 1);
		ft_putstr_fd("\033[7C", 1);
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if ((*cmdline)[0] == '\0' || all_white_space(*cmdline))
	{
		free(*cmdline);
		return (NULL);
	}
	add_history(*cmdline);
	return (*cmdline);
}
