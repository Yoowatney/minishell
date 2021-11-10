/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:16:48 by jlim              #+#    #+#             */
/*   Updated: 2021/11/10 19:37:11 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_string_util(t_env *change, char **str)
{
	char	*key;
	char	*value;
	char	*result;
	t_env	*export;

	export = change;
	key = ft_strdup(export->key);
	value = export->value;
	result = ft_strjoin(key, "=\"");
	result = ft_strjoin(result, value);
	result = ft_strjoin(result, "\"");
	*str = result;
}

char	**export_string(t_env *env)
{
	t_env	*change;
	char	**export_str;
	char	**return_value;
	char	*str;

	change = env;
	export_str = ft_malloc(sizeof(char *) * (env_size(env) + 1));
	return_value = export_str;
	while (1)
	{
		str = *export_str;
		export_string_util(change, &str);
		*export_str = str;
		export_str++;
		if (change->next)
			change = (change)->next;
		else
			break ;
	}
	*export_str = NULL;
	return (return_value);
}

char	**sort_list(char **export_str, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (export_str[j + 1] && (ft_strncmp(export_str[j],
						export_str[j + 1], ft_strlen(export_str[j])) > 0))
			{
				temp = export_str[j];
				export_str[j] = export_str[j + 1];
				export_str[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	print_export_fd(t_list **cmd_head, char **export_str)
{
	if ((*cmd_head)->next && (*cmd_head)->next->type == PIPE)
	{	
		while (*export_str)
		{
			ft_putstr_fd("declare -x ", (*cmd_head)->pipe[1]);
			ft_putstr_fd(*export_str, (*cmd_head)->pipe[1]);
			ft_putstr_fd("\n", (*cmd_head)->pipe[1]);
			export_str++;
			if (!*export_str)
				break ;
		}
	}
	else
	{
		while (*export_str)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(*export_str, 1);
			ft_putstr_fd("\n", 1);
			export_str++;
			if (!*export_str)
				break ;
		}
	}
}

void	print_export(t_env **env, t_list **cmd_head)
{
	char	**export_str;
	char	**tmp;

	export_str = export_string(*env);
	tmp = export_str;
	sort_list(export_str, env_size(*env));
	print_export_fd(cmd_head, export_str);
	free_str(tmp);
}
