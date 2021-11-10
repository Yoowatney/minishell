#include "minishell.h"

void	make_node(char **buf, int type, t_list **g_list)
{
	t_list *node;

	if (*buf == NULL)
		return ;
	node = ft_lstnew(*buf);
	node -> length = 1;
	node -> type = type;
	*buf = NULL;
	if (*g_list == NULL)
	{
		*g_list = node;
	}
	else
	{
		ft_lstadd_back(g_list, node);
	}
}

int	add_arg(char **buf, t_list *g_list)
{
	char	**temp;
	int		i;

	i = 0;
	if (*buf == NULL)
		return (1);
	temp = malloc(sizeof(char *) * (ft_lstlast(g_list)->length + 2));
	if (temp == NULL)
		error_check("");
	while (i < ft_lstlast(g_list)->length)
	{
		temp[i] = ft_lstlast(g_list)->cmd_table[i];
		i++;
	}
	if (ft_lstlast(g_list)->length > 0)
		free(ft_lstlast(g_list)->cmd_table);
	temp[i++] = *buf;
	temp[i] = NULL;
	*buf = NULL;
	ft_lstlast(g_list)->cmd_table = temp;
	ft_lstlast(g_list)->length++;
	return (1);
}

int	make_string(char c, char **buf)
{
	int			size;
	char		*temp;

	if (*buf == NULL)
	{
		(*buf) = malloc(sizeof(char));
		if (*buf == NULL)
			error_check("");
		**buf = '\0';
	}
	size = ft_strlen(*buf);
	temp = malloc(sizeof(char) * (size + 2));
	if (temp == NULL)
		error_check("");
	ft_strlcpy(temp, *buf, size + 1);
	temp[size] = c;
	temp[size + 1] = '\0';
	free(*buf);
	
	*buf = temp;
	return (1);
}