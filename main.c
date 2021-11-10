/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 05:04:10 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_list = NULL;
unsigned char	exit_status;

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
		new = malloc(sizeof(t_env));
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

int	main(int argc, char *av[], char *envp[])
{
	char	*cmdline;
	t_env	*env;
	t_list	*cmd_head;
	t_list	*redir_head;

	cmd_head = NULL;
	redir_head = NULL;
	env = NULL;
	exit_status = 0;
	if (argc != 1)
		ft_putstr_fd("Usage : \"./minishell\"\n", 2), exit(0);
	init(argc, av, envp, &env);
	while (1)
	{
		if (cmdline_start(&cmdline) == NULL)
			continue ;
		if (tokenizer(cmdline, &env) < 0)
		{
			ft_putstr_fd("pasing error\n", 2);
			if (g_list != NULL)
				g_list->cmdline = cmdline, all_free(&g_list);
			else
				free(cmdline);
			system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");
			continue ;
		}
		reparse_rewind(&g_list);

		split_cmd(&cmd_head, g_list), split_redir(&redir_head, g_list);
		g_list->cmd_list = cmd_head;
		g_list->redir_list = redir_head;
		g_list->cmdline = cmdline;

		while (cmd_head != NULL)
		{
			int copy[2];

			if (process_redir_node(redir_head, cmd_head, copy) < 0)
				break ;
			execute_bin(cmd_head, &env);
			dup2(copy[0], STDIN_FILENO);
			dup2(copy[1], STDOUT_FILENO);
			close(copy[0]);
			close(copy[1]);
			if (cmd_head->next)
				cmd_head = cmd_head->next, redir_head = redir_head->next;
			else
				break ;
		}
		rewind_list(&cmd_head);
		while (waitpid(cmd_head->pid, &cmd_head->exit_status, 0) > 0)
		{
			if (cmd_head->next)
				cmd_head = cmd_head->next;
		}
		if (exit_status == 0)
			exit_status = (unsigned char)(cmd_head->exit_status/256);
		all_free(&g_list);

		int fd;
		fd = open("Makefile", O_WRONLY);
		printf("\ncheck fd is 3 : %d\n\n", fd);
		close(fd);
		system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");
	}
}
