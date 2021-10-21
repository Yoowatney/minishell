#include "minishell.h"

char *get_name(char *str)
{
	int	i;
	int j;
	char *name;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=') //name=value
		i++;
	if (i > 0 && str[i - 1] == '+') //name+=value
		i--;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (0);
	while (j < i)
	{
		name[j] = str[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

char *get_value(char *str)
{
	int	i;
	int j;
	char *value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=') //name=value
		i++;
	if (str[i])
		i++;
	value = malloc(sizeof(char) * (ft_strlen(str) -i +1));
	if (!value)
		return (0);
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

int		name_exists(t_list *envp_data, char **cmd_table)
{
	while((envp_data))
	{
		if (!ft_strcmp(get_name(cmd_table[1]), get_name((envp_data)->cmd_table[0])))
		{
			return(1);
		}
		(envp_data) = (envp_data)->next;
	}
	return	(0);
}

int		equal_exists(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=') //name=value
		i++;
	if (i > 0 && str[i] == '=') //name+=value
		return(1);
	return(0);
}

int		plus_exists(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=') //name=value
		i++;
	if (i > 0 && str[i - 1] == '+') //name+=value
		return(1);
	return(0);
}

void    print_export(t_list *envp_data)
{
    int i;
	char *str;
	char *next_str;

    i = 0;
	str = envp_data->cmd_table[0];
	next_str = envp_data->next->cmd_table[0];
	while((envp_data))
	{
		if (ft_strcmp(envp_data->cmd_table[0]," "))
		{
			if (equal_exists(envp_data->cmd_table[0]))
				printf("declare -x %s=\"%s\"\n",get_name(envp_data->cmd_table[0]),get_value(envp_data->cmd_table[0]));
			else
				printf("declare -x %s\n",get_name(envp_data->cmd_table[0]));
		}
		envp_data= envp_data->next;
	}
}

void    ft_export(t_list **envp_data, char **cmd_table)
{
	int i;
	char *cmd_name;
	// char *str;
	i = 1;
	if (cmd_table[1])
	{
		while(cmd_table[i]) //export hi=welcome
		{
			if (name_exists(*envp_data,cmd_table))
				remove_envp(envp_data,cmd_table[i]);// 삭제
			// if (plus_exists(cmd_table[i]))
			// 	printf("plus");
			ft_lstadd_back(envp_data, ft_lstnew(ft_strdup(cmd_table[i])));//추가
			i++;
		}
	}
	else            //export
		print_export((*envp_data));
	cmd_name = get_name((*envp_data)->cmd_table[0]);
}
