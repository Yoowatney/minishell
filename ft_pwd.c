#include "libft/libft.h"
#include "minishell.h"

void ft_pwd(t_list *envp_data, char **cmd_table)
{
	// pwd -n =>	pwd: -n: invalid option
	//				pwd: usage: pwd [-LP]
	if (cmd_table[1] && cmd_table[1][0] == '-')
	{
		printf("pwd: %s: invalid option\n", cmd_table[1]);
		printf("pwd: usage: pwd [-LP]\n");
	}
	else
		while((envp_data))
		{
			if (!ft_strcmp("PWD", get_name((envp_data)->cmd_table[0])))
			{
				printf("%s\n",get_value(envp_data->cmd_table[0]));
			}
			(envp_data) = (envp_data)->next;
		}
}
