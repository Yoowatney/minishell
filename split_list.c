#include "minishell.h"

void	split_cmd_node(t_list *go, t_list *ret)
{
	while (go) 
	{
		if (go->type == TOKEN_END || go->type == PIPE)
		{
			ret->cmd_table = duplicate_table(go->cmd_table);
			ret->type = go->type;
			ret->length = go->length;
			ret->exit_status = go->exit_status;
			ret->infile = go->infile;
			ret->outfile = go->outfile;
		}
		else if (go->type == CRITERIA)
			ret = ret -> next;
		if (go->next != NULL)
			go = go->next;
		else
			break ;
	}
	return ;
}

void	split_redir_node(t_list *go, t_list *ret)
{
	char	**redir_table;
	int		*redir_type_table;
	int		size;
	int		i;

	redir_table = NULL;
	size = 0;
	while (go)
	{
		if (go->type == L_REDIR || go->type == R_REDIR)
		{
			i = 0;
			size = get_size(ret->cmd_table);
			redir_table = malloc(sizeof(char *) * (size + 2));
			while (ret->cmd_table && ret->cmd_table[i] != NULL)
			{
				redir_table[i] = ft_strdup(ret->cmd_table[i]);
				i++;
			}
			redir_table[i++] = ft_strdup(go->cmd_table[0]);
			redir_table[i] = NULL;
			for (int j = 0; ret->cmd_table && ret->cmd_table[j] != NULL; j++)
			{
				free(ret->cmd_table[j]);
				ret->cmd_table[j] = NULL;
			}
			free(ret->cmd_table);
			ret->cmd_table = redir_table;
			
			i = 0;
			size = get_file_size(ret->file_type_table);
			redir_type_table = malloc(sizeof(int) * (size + 2));
			while (ret->file_type_table && ret->file_type_table[i])
			{
				redir_type_table[i] = ret->file_type_table[i];
				i++;
			}
			redir_type_table[i++] = go->type;
			redir_type_table[i] = 0;
			free(ret->file_type_table);
			ret->file_type_table = redir_type_table;
			ret->type = go->type;
		}
		else if (go->type == CRITERIA)
			ret = ret->next;
		if (go->next != NULL)
			go = go->next;
		else
			break ;
	}
	return ;
}

