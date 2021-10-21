#include "minishell.h"

void	remove_envp(t_list **envp_data, char *var)
{
	t_list *element;
	
	int i;

	i =0;
	element= *envp_data;
	while (element)
	{
		/*if (!ft_strcmp(get_name(element->var[0]), get_name(var))) // leak*/
		if (ft_strncmp(element->cmd_table[0], var, ft_strlen(var)))
		{
			printf("pass\n");
			free(element->cmd_table[0]);
			element->cmd_table[0] = malloc(sizeof(char));
			element->cmd_table[0][0] = '\0';
			/*element->var[0] = "";*/
			/*free();*/
		}
		element = element->next;
	}
}

char	*get_key(char *env)
{
	char	*ret;
	int		i;

	i = 0;
	ret = env;
	while (env[i] != '=')
		i++;
	ret[i] = '\0';
	return (ret);
}

int	ft_unset(t_list **envp_data, char **cmd_table)
{
	t_list	*temp;
	int		i;
	char	*var;

	i = 0;
	var = cmd_table[1];
	temp = *envp_data;
	if (var == NULL)
		return (PARSE_ERROR);
	while (temp != NULL)
	{
		if (ft_strncmp(get_key(temp->cmd_table[0]), var, ft_strlen(var)))
		{
			free(temp->cmd_table[0]);
			temp->cmd_table[0] = malloc(sizeof(char));
			temp->cmd_table[0][0] = '\0';
		}
		temp = temp -> next;
	}
	return (0);
}
