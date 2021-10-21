/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:54:03 by yoyoo             #+#    #+#             */
/*   Updated: 2021/10/21 03:25:58 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int		ft_strcmp(const char *s1, const char *s2)
 {
 	int	i;
 
 	i = 0;
 	while (s1[i] == s2[i] && s1[i] && s2[i])
 		i++;
 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
 }

char *ft_strcat(char *d, const char *s)
{
    char *p = d;
    while(*d) d++;
    while(*s) *d++ = *s++;
    *d = '\0';
    return p;
}

void	rewind_list(t_list **list)
{
	while (*list && (*list)->prev)
		*list = (*list)->prev;
}

char	**allocate_envp(t_env *env)
{
	char	**ret;
	int		size;
	int		i;

	size = env_size(env);
	i = 0;
	ret = malloc(sizeof(char *) * (size + 1));
	if (ret == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(MALLOC_ERROR);
	}
	while (i < size)
	{
		ret[i] = ft_strdup(env->env_line);
		env = env -> next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	delete_key(t_list **envp_data)
{
	char	*replace;
	char	*temp;

	temp = (*envp_data)->cmd_table[0];
	while (*temp && *temp != '=')
		temp++;
	temp++;
	replace = ft_strdup(temp);
	/*printf("%s\n", replace);*/
	printf("!! def : %s\n!! aft : %s\n", (*envp_data)->cmd_table[0], replace);
	free((*envp_data)->cmd_table[0]);
	(*envp_data)->cmd_table[0] = replace;
	replace = NULL;
}
