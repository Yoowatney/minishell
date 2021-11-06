/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/06 11:29:08 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *g_list = NULL;

char	*get_key(char *envp)
{
	char	*ret;
	int		i;

	i = 0;
	while (envp[i] != '=')
	{
		i++;
	}
	envp[i] = '\0';
	ret = ft_strdup(envp);
	envp[i] = '=';
	return (ret);
}

char	*get_value(char	*envp)
{
	char	*ret;

	while (*envp != '=')
		envp++;
	envp++;
	ret = ft_strdup(envp);
	return (ret);
}

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	env_size(t_env *env)
{
	int	cnt;

	cnt = 1;
	if (!env)
		return (0);
	while (env->next != NULL)
	{
		cnt++;
		env = env -> next;
	}
	return (cnt);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*ptr;

	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	ptr = env_last(*env);
	ptr->next = new;
	new->prev = ptr;
}

int	init(int argc, char *argv[], char *envp[], t_env **env)
{
	extern int rl_catch_signals;
	int i;

	i = 0;
	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	t_env	*new;

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

int main(int argc, char *av[], char *envp[])
{
	char	*cmdline;
	int		error_num;
	t_env	*env;
	t_list	*cmd_head;
	t_list	*redir_head;

	cmd_head = NULL;
	redir_head = NULL;
	env = NULL;
	if (argc != 1)
	{
		ft_putstr_fd("error\n", 2);
		exit(0);
	}
	init(argc, av, envp, &env);
	while (1)
	{
		if (cmdline_start(&cmdline) == NULL)
			continue ;
		error_num = tokenizer(cmdline, &env), g_list->cmdline = cmdline;
		if (error_num < 0)
		{
			ft_putstr_fd("pasing error\n", 2);
			if (g_list != NULL)
				all_free(&g_list);
			continue ;
		}
		rewind_list(&g_list);
		re_parsing(&g_list);
		rewind_list(&g_list);

		cmd_head = create_list(g_list);
		split_cmd_node(g_list, cmd_head);
		rewind_list(&cmd_head);

		redir_head = create_list(g_list);
		split_redir_node(g_list, redir_head);
		rewind_list(&redir_head);
		rewind_list(&g_list);
		g_list->cmd_list = cmd_head;
		g_list->redir_list = redir_head;
		if (error_num < 0)
		{
			ft_putstr_fd("pasing error\n", 2);
			all_free(&g_list);
			free(cmdline);
			continue ;
		}
		while (cmd_head != NULL)
		{
			int copy[2];

			if (process_redir_node(redir_head, cmd_head, copy) < 0)
			{
				break ;
			}
			execute_bin(cmd_head, envp, &env);
			dup2(copy[0], STDIN_FILENO);
			dup2(copy[1], STDOUT_FILENO);
			close(copy[0]);
			close(copy[1]);
			if (cmd_head->next)
			{
				cmd_head = cmd_head->next;
				redir_head = redir_head->next;
			}
			else
				break ;
		}
		while (waitpid(-1, &cmd_head->exit_status, 0) > 0)
		{
			;
		}
		all_free(&g_list);
		system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");
	}
}
