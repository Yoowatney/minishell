/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/01 18:48:01 by yoyoo            ###   ########.fr       */
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
	t_list	*envp_data;
	int		error_num;
	t_env	*env = NULL;

	envp_data = NULL;
	if (argc != 1)
	{
		ft_putstr_fd("error\n", 2);
		exit(0);
	}
	init(argc, av, envp, &env);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		cmdline = readline("bash> ");
		if (cmdline == NULL)
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[7C", 1);
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		else if (cmdline[0] == '\0' || all_white_space(cmdline))
		{
			free(cmdline);
			continue ;
		}
		add_history(cmdline);
		error_num = tokenizer(cmdline);
		if (error_num < 0)
		{
			ft_putstr_fd("pasing error\n", 2), ft_lstclear(&g_list);
			free(cmdline);
			continue ;
		}

		rewind_list(&g_list);
		re_parsing(&g_list);
		rewind_list(&g_list);

		t_list *cmd_head;

		cmd_head = create_list(g_list);
		split_cmd_node(g_list, cmd_head);
		rewind_list(&cmd_head);

		t_list *redir_head;

		redir_head = create_list(g_list);
		split_redir_node(g_list, redir_head);
		rewind_list(&redir_head);

/*        printf("\n\t!!cmd_head node\n");
 *        for(; cmd_head != NULL; cmd_head = cmd_head -> next)
 *        {
 *            printf(" === cmd node ===\n");
 *            if (cmd_head->cmd_table != NULL)
 *            {
 *                for (int i = 0; cmd_head->cmd_table[i] != NULL; i++)
 *                {
 *                    printf("cmd : ||%s|| %d\n", cmd_head->cmd_table[i], cmd_head->type);
 *                }
 *            }
 *            else
 *            {
 *                printf("cmd : ||%s|| %d\n", (char *)cmd_head->cmd_table, cmd_head->type);
 *            }
 *            if (cmd_head -> next == NULL)
 *                break ;
 *
 *        }
 *        printf("\n\t!!redir_head node\n");
 *        for(; redir_head != NULL; redir_head = redir_head -> next)
 *        {
 *            printf(" === redir node ===\n");
 *            if (redir_head->cmd_table != NULL)
 *            {
 *                for (int i = 0; redir_head->cmd_table[i] != NULL; i++)
 *                {
 *                    printf("cmd : ||%s|| %d\n", redir_head->cmd_table[i], redir_head->file_type_table[i]);
 *                }
 *            }
 *            else
 *            {
 *                printf("file : ||%s|| %d\n", (char *)redir_head->cmd_table, redir_head->type);
 *            }
 *            if (redir_head -> next == NULL)
 *                break ;
 *        }*/

		/*rewind_list(&cmd_head);
		 *rewind_list(&g_list);
		 *ft_lstclear(&g_list);
		 *g_list = NULL;
		 *free(cmdline);
		 *continue ;*/

		rewind_list(&cmd_head);
		rewind_list(&g_list);
		rewind_list(&redir_head);
		while (cmd_head)
		{
			if (cmd_head->cmd_table == NULL)
			{
				error_num = -1;
				break ;
			}
			if (cmd_head->next != NULL)
				cmd_head = cmd_head->next;
			else
				break ;
		}

		if (error_num < 0)
		{
			ft_putstr_fd("pasing error\n", 2);
			free(cmdline);
			rewind_list(&cmd_head);
			rewind_list(&redir_head);
			rewind_list(&g_list);
			ft_lstclear(&cmd_head);
			ft_lstclear(&redir_head);
			ft_lstclear(&g_list);
			continue ;
		}
		rewind_list(&cmd_head);
		rewind_list(&redir_head);
		rewind_list(&g_list);

		while (cmd_head != NULL)
		{
			int copy[2];

			if (process_redir_node(redir_head, cmd_head, copy) < 0)
			{
				break ;
			}
			if (cmd_head->cmd_table != NULL)
				execute_bin(cmd_head, envp, env);
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
		int fd = open("t0", O_WRONLY);
		printf("fd : %d\n", fd);
		close(fd);

		rewind_list(&cmd_head);
		rewind_list(&redir_head);
		rewind_list(&g_list);
		ft_lstclear(&cmd_head);
		ft_lstclear(&redir_head);
		ft_lstclear(&g_list);
		g_list = NULL;
		cmd_head = NULL;
		redir_head = NULL;
		free(cmdline);
		/*system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");*/
	}
}
