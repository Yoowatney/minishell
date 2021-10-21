#include "minishell.h"

int ft_countrow(char *av[])
{
	int i;
	i = 0;
	while(av[i])
	{
		i++;	
	}
	return (i);
}

int	is_option_n(char *av)
{
	int i;

	i = 1;
	if (av[0] != '-')
		return (0);
	if (av[1] ==  '\0') // "-" 일 때
		return (0);
	while (av[i] == 'n') //n 여러개 일때 ex -nnn...
		i++;
	return (!av[i]);// -nnnl일 경우 0리턴
}

void find_name(t_list *envp_data, char *str)//str=$USER
{
	int i;
	char string[1024];
	char *new;

    i = 0;
	while (str[i+1])
	{
		string[i] = str[i+1];
		i++;
	}
	string[i]='\0';//string=USER
	i = 0;
	while((envp_data))
	{
		if (!ft_strncmp(get_name(envp_data->cmd_table[0]), string, ft_strlen(string)))
			{
				new = get_value(envp_data->cmd_table[0]);
				while(new[i])
				{
					if (new[i] == ' ' && new[i - 1] != ' ')
						ft_putstr_fd(" ", 1);
						/*printf(" ");*/
					else if (new[i] != ' ')
						ft_putchar_fd(new[i], 1);
						/*printf("%c", new[i]);*/
					i++;
				}
				return ;
			}
		envp_data= envp_data->next;
	}
}

void ft_echo(char *av[], t_list *envp_data)
{
	int	option_n;
	int argc;
	int	i;

	option_n=0;
	argc = ft_countrow(av);
	i =1;
	// printf("//%s//",av[1]);
	if (argc > 1) //2개 이상일때
		option_n = is_option_n(av[1]);//옵션이 있?
	while (av[i] && is_option_n(av[i])) //옵션 스킵
		i++;
	while (i < argc)
	{
		if (av[i][0] != '$')
			ft_putstr_fd(av[i], 1);
			/*printf("%s",av[i]);*/
		else
			find_name(envp_data,av[i]);
		if (i != argc)
			ft_putstr_fd(" ", 1);
			/*printf(" ");*/
		i++;
	}
	if (!option_n)
		ft_putstr_fd("\n", 1);
		/*printf("\n");*/
	fflush(stdout);
}
