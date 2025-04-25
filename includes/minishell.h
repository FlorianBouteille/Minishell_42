/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:01:16 by csolari           #+#    #+#             */
/*   Updated: 2025/04/25 17:33:53 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <strings.h>
# include <unistd.h>

extern int last_signal;


typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

/// ^ boolean  (lib stdbool.h, bool ture false)
/// qui nous permette de savoir si faut expendre les dollars
/// entre single quote pas d expension (bool = false) entre double oui(bool = 1)

typedef struct	s_file
{
	char			*name;
	char			*limiter;
	int				out_append;
	struct s_file	*next;
}					t_file;

typedef struct s_command
{
	int				index;
	int				number_commands;
	int				number_heredocs;
	int				skip_command;
	//int			out_append;
	t_file			*infile;
	t_file			*outfile;
	//char			*limiter;
	int				fd_heredoc;
	char			*value;
}					t_command;

typedef struct s_data
{
	int			number_of_commands;
	int			number_heredoc;
	int			stdin_copy;
	int			stdout_copy;
	int			exit_status;
	char		**envp;
	t_token		*tokens;
	t_command	**commands;
}					t_data;

// struct sigaction {
// 	void     (*sa_handler)(int);
// 	void     (*sa_sigaction)(int, siginfo_t *, void *);
// 	sigset_t   sa_mask;
// 	int        sa_flags;
// 	void     (*sa_restorer)(void);
// };

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_END
}					t_token_type;

// Lexing

t_token				*lex_string(char *str);
void				add_token(char *str, t_token **tokens);
t_token				*new_token(char *str);
int					get_word_len(char *str);
char				*make_word(char *str);
char				*add_spaces(char *str);
int					is_special(char c);

// Memory_utils
void				free_command(t_command *command);
void				free_command_tab(t_command **tab);
void				free_tokens(t_token **tokens);
void				ft_free_tab(char **tab);

// Parsing

t_command			*new_command(t_token *tokens, int index, int number_commands);
t_command			**build_command_tab(t_token *tokens);
t_file				*create_new_file(char *name, char *limiter, int out_append);
int					check_tokens(t_token *tokens, t_data **data);
void				add_file_back(t_file **files, char *name, char *limiter, int out_append);
void				free_all_data(t_data **data);
void				expand_variables(t_token *tokens);
int					is_variable_env(char *str);
int					count_number_variable(char *str);
char				*variable_name(char *str);


// Execution

void				exec_commands(t_data **data);
char				*get_path(char *str, char *envp[]);
int					get_heredocs(t_command **tab, t_data **data);
void				redirect_input(t_command *command, t_file *infile, int last);
void				redirect_output(t_file *outfile);
void				redirect_all_inputs(t_command *command, int pipe_fd[2]);
void				redirect_all_outputs(t_command *command, int pipe_fd[2]);
void				close_heredocs_fd(t_command **commands);


// Debug

void				print_tokens(t_token *token);
void				print_command(t_command *command);
void				print_command_tab(t_command **tab);
void				print_files(t_file *file);

// Error

void				lex_error(char *str, t_data **data);

#endif
