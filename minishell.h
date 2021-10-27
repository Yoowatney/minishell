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

#define TOKEN_END 499
#define PIPE 500
#define L_REDIR 501
#define R_REDIR 502

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

/* execute fct */
void	execute_bin(t_list *g_list, char *envp[], t_env *env);

/* token fct */
int		open_single_quote(char **line, char **buf);
int		open_double_quote(char **line, char **buf);
int		make_string(char c, char **buf);
int		tokenizer(char *line);
void	re_parsing(t_list **g_list);

/* utils */
void	rewind_list(t_list **list);
int		is_space(int c);
char	**allocate_envp(t_env *envp_data);
void	delete_key(t_list **envp_data);
int		env_size(t_env *env);
t_env	*env_last(t_env *env);
void	error_check();

