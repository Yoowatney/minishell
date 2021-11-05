#include "minishell.h"

int	check_builtin(t_list **cmd_head)
{

	if (ft_strcmp((*cmd_head)->cmd_table[0], "echo") == 0)
	{
		return (1);
	}
	if (ft_strcmp((*cmd_head)->cmd_table[0], "cd") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "pwd") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "export") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "unset") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "env") == 0)
		return (1);
	if (ft_strcmp((*cmd_head)->cmd_table[0], "exit") == 0)
		return (1);	
	return (0);
}

int	check_cmd(t_list **g_list, t_env **env, t_list **cmd_head)
{
	char	**my_envp = allocate_envp(*env);

	if (ft_strcmp((*cmd_head)->cmd_table[0], "echo") == 0)
	{
		builtin_echo(cmd_head);
	}
	
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "cd") == 0)
	{
		return (builtin_cd(g_list, cmd_head, my_envp));
	}
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "pwd") == 0)
	{
		builtin_pwd(cmd_head);
	}
	
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "export") == 0)
	{
		builtin_export(cmd_head, env, g_list);
	}
	
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "unset") == 0)
	{
		builtin_unset(cmd_head, env, g_list);
	}
	
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "env") == 0)
	{
		builtin_env(my_envp, cmd_head);
	}
	else if (ft_strcmp((*cmd_head)->cmd_table[0], "exit") == 0)
	{
		builtin_exit(g_list, env);
	}

	return (0);
}
