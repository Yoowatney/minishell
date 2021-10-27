/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:24 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/27 21:36:17 by yoyoo            ###   ########.fr       */
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
		error_check();
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

        for (; g_list != NULL; g_list = g_list->next)
		{
			printf(" --- node ---\n");
			for (int i = 0; g_list->cmd_table[i] != NULL; i++)
				printf("%s %d\n", g_list->cmd_table[i], g_list->type);
			if (g_list -> next == NULL)
				break ;
		}
		rewind_list(&g_list);
		re_parsing(&g_list);
		rewind_list(&g_list);
        printf("\n\n");
		for(; g_list != NULL; g_list = g_list -> next)
		{
			printf(" === node ===\n");
			if (g_list->cmd_table != NULL)
			{
				for (int i = 0; g_list->cmd_table[i] != NULL; i++)
				{
					printf("cmd : ||%s|| %d\n", g_list->cmd_table[i], g_list->type);
				}
			}
			else
			{
				printf("file : ||%s|| %d\n", g_list->file_name, g_list->type);
			}

		}
		continue ;
        exit(0);
		while (g_list != NULL)
		{
			execute_bin(g_list, envp, env);
			if (g_list -> next != NULL)
			{
				g_list = g_list -> next;
			}
			else
			{
				break ;
			}
		}
		int fd = open("./t0", O_WRONLY);
		printf("fd : %d\n", fd);
		close(fd);
		rewind_list(&g_list);
		ft_lstclear(&g_list);
		g_list = NULL;
		free(cmdline);
		/*system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");*/
	}
}
