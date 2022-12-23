/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:27:49 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 02:01:38 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "libgc/include/gc.h"
# include <sys/stat.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <paths.h>

# define OUT	1
# define IN  0

# define ECHO 1
# define PWD 2
# define CD 3
# define EXIT 4
# define UNSET 5
# define EXPORT 6
# define ENV 7

typedef struct s_arg
{
	char			*arg;
	struct s_arg	*next;
}				t_arg;

typedef struct s_red
{
	char			*file;
	bool			is_heredoc;
	int				fd;
	int				type;
	int				oflags;
	struct s_red	*next;
}				t_red;

typedef struct s_cmd
{
	t_arg			*exec;
	t_red			*red;
	int				fd_in;
	int				fd_out;
	int				cnt;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd;
	int		tmp_fd[2];
	int		pipes;
	int		tmp_st;
	pid_t	pid[2];
}				t_mini;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_glob
{
	t_gc	*gc;
	t_env	*venv;
	bool	is_runing;
	int		status;
}				t_glob;

extern t_glob	g_glob;

typedef enum e_tok
{
	WORD,
	VAR,
	RED,
	PIPE,
	END
}			t_tok;

// Important functions
bool	parse(char *line, t_mini *mini);

// constructors
t_mini	*new_mini(t_cmd *cmd, int pipes);
t_cmd	*new_cmd(t_arg *args, t_red *red);
t_red	*new_red(char *file, int type, int oflags, int is_heredoc);
t_arg	*new_arg(char *arg);

// append utils
void	push_cmd(t_cmd **cmd, t_cmd *new);
void	push_red(t_red **red, t_red *new);
void	push_arg(t_arg **arg, t_arg *new);
void	reset_mini(t_mini *mini);

// parsing utils
void	reset_mini(t_mini *mini);
char	*skip_ws(char *line);
char	*skip_quote(char *line, char qt);
t_tok	lookahead(char *line);
bool	check_syntax(char *line);
bool	parse_red(char **line, t_red **red);
char	*parse_arg(char *line, t_arg **arg);
bool	make_mini(char *line, t_mini *mini);
bool	parse(char *line, t_mini *mini);
char	*sq_mode(char **line);
char	*word_mode(char **line);
char	*word_inside_dq(char *line, char **word_arr, int *size);
char	*var_inside_dq(char *line, char **word_arr, int *size);
char	*dq_mode(char **line);
char	*dollar_mode(char **line);
int		ft_pipe(int fildes[2]);
void	reset_mini(t_mini *mini);
char	*skip_ws(char *line);
char	*skip_quote(char *line, char qt);
t_tok	lookahead(char *line);
int		ft_pipe(int fildes[2]);
char	*sq_mode(char **line);
char	*word_mode(char **line);
char	*word_inside_dq(char *line, char **word_arr, int *size);
char	*var_inside_dq(char *line, char **word_arr, int *size);
char	*dq_mode(char **line);
char	*dollar_mode(char **line);
int		heredoc(char *delim);
t_red	*init_red(char **line);
bool	parse_red(char **line, t_red **red);
void	*gc_filter(void *ptr, t_gc_flag append_flag);
char	*ft_strndup(char *str, int n);
char	*ft_chardup(char c);
int		ft_isspace(char c);

void	handle_quotes(char **line, int quote[2]);
void	_error_exit(char *title, char *msg, int status);
void	set_status(int status);
int		get_status(void);

void	_error(char *title, char *msg, int status);
void	execute(t_mini *mini);

char	*getkey(char *var);
char	*getvalue(char *var);
void	push_venv(char *key, char *value);
void	venv_init(char **env);
char	*ft_getenv(char *key);
char	**export_env_arr(void);
char	**export_args_arr(t_arg *arg);

//init function
void	save_io(t_mini *mini);

// redirection
void	redirection(t_cmd *cmd);

//builtins
void	cd(char **path);
void	env(char **av);
void	echo(char **para);
void	ft_exit(char **args);
void	export(char **args);
void	unset(char **args);
void	pwd(void);

//execution
void	exec(t_mini *mini);
int		isbuiltins(char *args);
void	exec_builtins(int builtin, char **para);
void	close_file(int *fd1, int std);

//helper
int		ft_strcmp(char *s1, char *s2);
char	*get_path(char **para);
void	modify_var(char *key, char *value);
void	ft_dup2(int dest, int src);
void	ft_dup2(int dest, int src);

// signal handling
void	sig_init(void);
void	sig_restore(void);

#endif