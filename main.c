/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/13 20:24:52 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	g_exit_status = 0;

int	init(int argc, char *argv[], char *envp[], t_env **env)
{
	extern int	rl_catch_signals;
	int			i;
	t_env		*new;

	i = 0;
	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	while (envp[i] != NULL)
	{
		new = ft_malloc(sizeof(t_env));
		if (new == NULL)
			error_check("");
		new -> next = NULL;
		new -> prev = NULL;
		new -> env_line = ft_strdup(envp[i]);
		new -> key = get_key(envp[i]);
		new -> value = get_value(envp[i]);
		env_add_back(env, new);
		i++;
	}
	return (1);
}

int	all_white_space(char *cmdline)
{
	while (*cmdline)
	{
		if (!is_space(*cmdline))
			return (0);
		cmdline++;
	}
	return (1);
}

void	init_main(t_list **cmd_head, t_list **list,
		t_list **redir_head, t_env **env)
{
	*cmd_head = NULL;
	*list = NULL;
	*redir_head = NULL;
	*env = NULL;
}

int	main(int argc, char *av[], char *envp[])
{
	char	*cmdline;
	t_env	*env;
	t_list	*cmd_head;
	t_list	*redir_head;
	t_list	*list;

	init_main(&cmd_head, &list, &redir_head, &env);
	if (argc != 1)
		ft_putstr_fd("Usage : \"./minishell\"\n", 2), exit(0);
	init(argc, av, envp, &env);
	while (1)
	{
		if (main_tokenizer(&cmdline, &env, &list) == 1)
			continue ;
		split_list(&cmd_head, &redir_head, list, cmdline);
		execute_process(&cmd_head, &env, &list, &redir_head);
		wait_process(&cmd_head, &list);
	}
}
