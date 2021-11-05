#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>

/* TYPE */


#define EMPTY		497
#define CRITERIA	498
#define TOKEN_END	499
#define PIPE		500
#define L_REDIR		501
#define R_REDIR		502
#define HEREDOC		503
#define A_REDIR		504

#define NOT_EXECUTABLE	126
#define NOT_FOUND		127

typedef struct s_env
{
	struct	s_env	*prev;
	struct	s_env	*next;
	char	*key;
	char	*value;
	char	*env_line;
	
}				t_env;


/* signal fct */

void	sig_handler(int signum);
void	bin_sig_handler(int signum);
void	init_execute_bin(void);

/* token fct */

int		open_single_quote(char **line, char **buf);
int		open_double_quote(char **line, char **buf, t_env **env);
int		make_string(char c, char **buf);
int		tokenizer(char *line, t_env **env);
void	re_parsing(t_list **g_list);
void	make_redir_node(char **buf, int type, t_list **redir_node);
char	**change_dollar(char **line, char **buf, t_env *env);

/* parsing fct */

int		get_size(char **cmd_table);
void	re_parsing(t_list **g_list);
void	split_cmd_node(t_list *go, t_list *ret);
void	split_redir_node(t_list *go, t_list *ret);
char	**duplicate_table(char **cmd_table);
int		get_file_size(int *files);
t_list	*create_list(t_list *go);

/* execute fct */

void	execute_bin(t_list *g_list, char *envp[], t_env **env, char **cmdline);
int		process_redir_node(t_list *redir_head, t_list *cmd_head, int copy[]);


void	split_cmd_node(t_list *go, t_list *ret);
void	split_redir_node(t_list *go, t_list *ret);
t_list	*create_list(t_list *go);

/* utils */

void	rewind_list(t_list **list);
int		is_space(int c);
char	**allocate_envp(t_env *envp_data);
void	delete_key(t_list **envp_data);
int		env_size(t_env *env);
t_env	*env_last(t_env *env);
void	error_check(char *str);


/* check_cmd */
int		check_builtin(t_list **cmd_head);
int		check_cmd(t_list **g_list, char **cmdline, t_env **env, t_list **cmd_head);

/* exit */
void	all_free(t_list **g_list, char **cmdline);
int		builtin_exit(t_list **g_list, char **cmdline, t_env **env);

/* env */
int		builtin_env(char **my_envp, t_list **cmd_head);

/* ft_strcmp */
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_ch(char *s1, char c);
char	*ft_strjoin_not(char *s1, char *s2);

/* echo */
int		builtin_echo(t_list **cmd_head);

/* pwd */
int		builtin_pwd(t_list **cmd_head);

/* cd */
int		builtin_cd(t_list **g_list, t_list **cmd_head, char **my_envp);

/* export */
int		builtin_export(t_list **cmd_head, t_env **env, t_list **g_list);

/* env관련 main */
char	*get_key(char *envp);
char	*get_value(char *envp);
void	env_add_back(t_env **env, t_env *new);

/* unset */
int		builtin_unset(t_list **cmd_head, t_env **env, t_list **g_list);
