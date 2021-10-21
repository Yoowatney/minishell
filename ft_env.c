#include "libft/libft.h"
#include "minishell.h"
//export hi=welcome
//name =hi
//value=welcome

int equal_exist(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			return	(1);
		i++;
	}
	return (0);
}

void ft_env(t_list *envp_data){
	while (envp_data)
	{
		if(equal_exist(envp_data->cmd_table[0]))
			printf("%s\n", envp_data->cmd_table[0]);
		envp_data = envp_data->next;	
	}
}
