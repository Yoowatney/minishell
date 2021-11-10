#include "minishell.h"

unsigned char	g_exit_status;

int	main_tokenizer(char **cmdline, t_env **env, t_list **g_list)
{
	if (cmdline_start(cmdline) == NULL)
		return (1);
	if (tokenizer(*cmdline, env, g_list) < 0)
	{
		ft_putstr_fd("pasing error\n", 2);
		g_exit_status = 200;
		if (*g_list != NULL)
			(*g_list)->cmdline = *cmdline, all_free(g_list);
		else
			free(*cmdline);
		system("leaks minishell > leaks_result; cat leaks_result | grep leaked; rm -rf leaks_result");
		return (1);
	}
	reparse_rewind(g_list);
	return (0);
}

void	split_list(t_list **cmd_head, t_list **redir_head, t_list *g_list, char *cmdline)
{
	split_cmd(cmd_head, g_list);
	split_redir(redir_head, g_list);
	g_list->cmd_list = *cmd_head;
	g_list->redir_list = *redir_head;
	g_list->cmdline = cmdline;
}
