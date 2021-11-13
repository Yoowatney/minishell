/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:50:27 by yoyoo             #+#    #+#             */
/*   Updated: 2021/11/14 02:45:22 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>

/* TYPE */
# define EMPTY			497
# define CRITERIA		498
# define TOKEN_END		499
# define PIPE			500
# define L_REDIR		501
# define R_REDIR		502
# define HEREDOC		503
# define A_REDIR		504

# define NOT_EXECUTABLE	126
# define NOT_FOUND		127

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*key;
	char			*value;
	char			*env_line;
}				t_env;

/* sys call */
void	*ft_malloc(int size);
void	ft_dup2(int old, int newe);
int		ft_dup(int fd);
void	ft_close(int fd);
void	ft_chdir(char *dir);

/* signal fct */
void	sig_handler(int signum);
void	bin_sig_handler(int signum);
void	init_execute_bin(void);

/* token fct */
int		tokenizer(char *line, t_env **env, t_list **list);
void	re_parsing(t_list **list);
void	make_redir_node(char **buf, int type, t_list **redir_node);
int		all_white_space(char *cmdline);
char	*cmdline_start(char	**cmdline);
int		make_pipe_node(char **buf, char **line, int *type, t_list **list);
int		make_L_redir_node(char **buf, char **line, int *type, t_list **list);
int		make_R_redir_node(char **buf, char **line, int *type, t_list **list);
int		main_tokenizer(char **cmdline, t_env **env, t_list **list);
void	split_list(t_list **cmd_head, t_list **redir_head,
			t_list *list, char *cmdline);

/* token_util */
void	make_node(char **buf, int type, t_list **list);
int		add_arg(char **buf, t_list *list);
int		make_string(char c, char **buf);

/* token_util2 */
int		open_single_quote(char **line, char **buf, t_list **list);
int		open_double_quote(char **line, char **buf, t_env **env,
			t_list **list);
int		is_white_space(char **line, char **buf, int *type, t_list **list);
int		is_dollar(char **line, char **buf, t_env **env);

/* change_dollar */
char	**change_dollar(char **line, char **buf, t_env *env);

/* change_dollar2 */
char	**change_dollar2_util(char **line, char **buf);
char	**change_dollar2_util2(char **check, t_env *env,
			char **buf, char **line);
char	**change_dollar2(char **line, char **buf, t_env *env);

/* parsing fct */
int		get_size(char **cmd_table);
void	re_parsing(t_list **list);
void	split_cmd_node(t_list *go, t_list *ret);
void	split_redir_node(t_list *go, t_list *ret);
char	**duplicate_table(char **cmd_table);
int		get_file_size(int *files);
t_list	*create_list(t_list *go);
int		choice_condition(int type);
void	init_redir_node(char ***redir_table, int **redir_type_table);
void	reparse_rewind(t_list **list);
void	split_cmd(t_list **cmd_head, t_list *list);
void	split_redir(t_list **redir_head, t_list *list);

/* execute fct */

void	execute_bin(t_list *cmd_head, t_env **env, t_list **list);
int		process_redir_node(t_list *redir_head, t_list *cmd_head, int copy[]);
void	execute(t_list *cmd_head, t_list *list, t_env **env, char **my_envp);
void	execute_process(t_list **cmd_head, t_env **env,
			t_list **list, t_list **redir_head);
void	wait_process(t_list **cmd_head, t_list **list);

/* execute utils */
void	execute_init(int *pipe_open, int *fd);

/* redirection utils */
void	close_L_fd(int fd, int copy[]);
void	close_R_fd(int fd, int copy[]);

void	right_redir(t_list *cmd_head, t_list *redir_head, int fd, int i);
void	append_redir(t_list *cmd_head, t_list *redir_head, int fd, int i);
void	heredoc_redir(t_list *cmd_head, t_list *redir_head, int fd, int i);
int		left_redir(t_list *redir_head, int *fd, int i, int copy[]);

void	split_cmd_node(t_list *go, t_list *ret);
void	split_redir_node(t_list *go, t_list *ret);
t_list	*create_list(t_list *go);

/* main utils */
void	rewind_list(t_list **list);
void	rewind_env(t_env **env);
int		is_space(int c);
char	**allocate_envp(t_env *envp_data);
void	delete_key(t_list **envp_data);
int		env_size(t_env *env);
t_env	*env_last(t_env *env);
void	error_check(char *str);
char	*get_key(char *envp);
char	*get_value(char	*envp);
t_env	*env_last(t_env *env);
int		env_size(t_env *env);
void	env_add_back(t_env **env, t_env *newe);
void	free_cmd_table(char **cmd_table);

/* check_cmd */
int		check_builtin(t_list **cmd_head);
int		cmd_builtin(t_list **list, t_env **env,
			t_list **cmd_head, char **my_envp);

/* exit */
void	all_free(t_list **list);
int		builtin_exit(t_list **list, t_env **env, t_list **cmd_head);

/* env */
int		builtin_env(char **my_envp, t_list **cmd_head);

/* ft_strcmp */
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_ch(char *s1, char c);
char	*ft_strjoin_not(char *s1, char *s2);

/* echo */
int		delete_null_util(t_list **cmd_head);
char	**delete_null(t_list **cmd_head);
int		builtin_echo(t_list **cmd_head);

/* echo_util */
int		echo_util(t_list **cmd_head, char **print, int n_flag);
void	echo_util2(char **print, int n_flag);

/* pwd */
int		builtin_pwd(t_list **cmd_head);

/* cd */
int		builtin_cd(t_list **cmd_head, char **my_envp, t_env **env);

/* cd_only */
int		only_cd(char **cd_cmd, char **my_envp, t_env **env);

/* cd_oldpwd */
char	*check_oldpwd_value(char **my_envp);
t_env	*check_oldpwd(t_env **env);
void	save_oldpwd(t_env **env);

/* cd_util */
char	*check_home(char **my_envp);
char	*check_updir(void);
int		check_end_slash(char *value);
char	*check_user(char **my_envp, char *user);
int		print_not_home(char **cd_cmd);

/* export */
int		builtin_export(t_list **cmd_head, t_env **env);

/* export_str */
void	export_string_util(t_env *change, char **str);
char	**export_string(t_env *env);
char	**sort_list(char **export_str, int size);
void	print_export_fd(t_list **cmd_head, char **export_str);
void	print_export(t_env **env, t_list **cmd_head);

/* export_util */
int		check_plus_equal(char *cmd_table);
t_env	*check_key(t_env *env, char *key);
void	free_str(char **export_str);
char	*get_export_key(char *cmd_table);
char	*get_export_value(char *cmd_table);

/* env관련 main */
char	*get_key(char *envp);
char	*get_value(char *envp);
void	env_add_back(t_env **env, t_env *newe);

/* unset */
int		builtin_unset(t_list **cmd_head, t_env **env);
void	free_env(t_env **check, t_env **tmp, t_env **env);

/* builtin util */
int		check_equal_sign(char *cmd_table);
int		check_alpha(char *cmd_table);
int		check_num(char *cmd_table);
int		check_identifier(char *cmd_table, t_list **cmd_head, int *ret);

/* error_print */
void	print_valid(t_list **cmd_head, char *cmd_table);
void	no_file_cd(char **cd_cmd, char *check_home);
void	no_file_env(t_list **cmd_head, char *cmd_table);
int		error_exit1(t_list **cmd_head);
int		error_exit2(t_list **cmd_head);

/* pipe_exist */
int		pipe_exist(t_list *list);

#endif
