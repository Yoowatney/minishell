/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 04:54:47 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/11 18:52:47 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, t_list **list)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	all_free(list);
	exit(NOT_FOUND);
}

char	*select_cmd_table(t_list *cmd_head, char **prefix, int *i)
{
	char	*file_name;
	int		j;
	char	**check;

	j = 0;
	check = NULL;
	if (cmd_head->cmd_table[0][0] != '/')
	{
		prefix[*i] = ft_strjoin(prefix[*i], "/");
		file_name = ft_strjoin(prefix[*i], cmd_head->cmd_table[0]);
	}
	else
	{
		check = ft_split(cmd_head->cmd_table[0], '/');
		while (check[j] != NULL)
			j++;
		j--;
		file_name = cmd_head->cmd_table[0];
		cmd_head->cmd_table[0] = ft_strdup(check[j]);
	}
	(*i)++;
	free_cmd_table(check);
	return (file_name);
}

int	choice_env_condition(t_env **env)
{
	if ((*env)->next != NULL)
		(*env) = (*env)->next;
	else
	{
		rewind_env(env);
		return (1);
	}
	return (0);
}

void	free_in_child(char **my_envp, t_env **env)
{
	t_env	*temp;

	while ((*env) != NULL)
	{
		temp = *env;
		free(temp->key);
		free(temp->value);
		free(temp->env_line);
		*env = (*env)->next;
		free(temp);
	}
	free_cmd_table(my_envp);
}

void	execute(t_list *cmd_head, t_list *list, t_env **env, char **my_envp)
{
	char	**prefix;
	char	*file_name;
	int		i;

	signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL);
	while ((*env) != NULL)
	{
		i = 0;
		prefix = ft_split((*env)->value, ':');
		while (prefix[i] != NULL)
		{
			file_name = select_cmd_table(cmd_head, prefix, &i);
			if (execve(file_name, cmd_head->cmd_table, my_envp) < 0)
			{
				free(file_name);
				continue ;
			}
		}
		free(prefix);
		if (choice_env_condition(env) == 1)
			break ;
	}
	free_in_child(my_envp, env);
	print_error(cmd_head->cmd_table[0], &list);
}
