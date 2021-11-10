/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/10 15:23:34 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_status = 0;

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

void	init_main(t_list **cmd_head, t_list **g_list, t_list **redir_head, t_env **env)
{
	*cmd_head = NULL;
	*g_list = NULL;
	*redir_head = NULL;
	*env = NULL;
}

int	main(int argc, char *av[], char *envp[])
{
	char	*cmdline;
	t_env	*env;
	t_list	*cmd_head;
	t_list	*redir_head;
	t_list	*g_list;

	init_main(&cmd_head, &g_list, &redir_head, &env);
	if (argc != 1)
		ft_putstr_fd("Usage : \"./minishell\"\n", 2), exit(0);
	init(argc, av, envp, &env);
	while (1)
	{
		if (main_tokenizer(&cmdline, &env, &g_list) == 1)
			continue ;
		split_list(&cmd_head, &redir_head, g_list, cmdline);
		while (cmd_head != NULL)
		{
			int copy[2];

			if (process_redir_node(redir_head, cmd_head, copy) < 0)
				break ;
			execute_bin(cmd_head, &env, &g_list);
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
		if (g_exit_status == 0)
			g_exit_status = (unsigned char)(cmd_head->exit_status/256);
		all_free(&g_list);

		int fd;
		fd = open("Makefile", O_WRONLY);
		printf("\ncheck fd is 3 : %d\n\n", fd);
		close(fd);
		system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");
	}
}
