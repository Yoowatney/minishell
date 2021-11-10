/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 07:27:31 by jlim              #+#    #+#             */
/*   Updated: 2021/11/11 07:27:33 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_cd(char **cd_cmd, char **my_envp, t_env **env)
{
	if (!(check_home(my_envp)))
		return (print_not_home(cd_cmd));
	save_oldpwd(env);
	if (chdir(check_home(my_envp)) < 0)
		no_file_cd(cd_cmd, check_home(my_envp));
	return (0);
}
