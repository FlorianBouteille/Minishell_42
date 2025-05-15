/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:01:16 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 12:41:41 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/includes/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>
# include <unistd.h>

extern int					g_last_signal;
typedef struct sigaction	t_sigaction;

typedef struct s_token
{
	char					*value;
	int						type;
	struct s_token			*next;
}							t_token;

/// ^ boolean  (lib stdbool.h, bool ture false)
/// qui nous permette de savoir si faut expendre les dollars
/// entre single quote pas d expension (bool = false) entre double oui(bool = 1)

typedef struct s_file
{
	char					*name;
	char					*limiter;
	int						type;
	struct s_file			*next;
}							t_file;

typedef struct s_command
{
	int						index;
	int						number_commands;
	int						number_heredocs;
	int						skip_command;
	int						stop_redir;
	t_file					*file;
	int						fd_heredoc;
	char					*value;
	char					**cmd_tab;
}							t_command;

typedef struct s_data
{
	int						number_of_commands;
	int						number_heredoc;
	int						stdin_copy;
	int						stdout_copy;
	int						exit_status;
	int						*pid_tab;
	char					**envp;
	t_token					*tokens;
	t_command				**commands;
}							t_data;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_END
}							t_token_type;

typedef enum e_redir_type
{
	IN,
	OUT,
	OUT_APPEND,
	HEREDOC
}							t_redir_type;

// Lexing

t_token						*lex_string(char *str);
void						add_token(char *str, t_token **tokens);
t_token						*new_token(char *str);
int							get_word_len(char *str);
char						*make_word(char *str);
char						**copy_tab(char **tab);
char						*add_spaces(char *str);
int							is_special(char c);
void						init_tab(int *tab, int size);
int							check_line(char *line);
int							check_line_bis(char *line);

// Memory_utils

void						free_command(t_command *command);
void						free_command_tab(t_command **tab);
void						free_tokens(t_token **tokens);
void						free_file_list(t_file *files);
void						ft_free_tab(char **tab);
void						free_all_data(t_data **data);

// Parsing

t_command					*new_command(t_token *tokens, int index,
								int number_commands);
t_command					**build_command_tab(t_data *data);
t_file						*create_new_file(char *name, char *limiter,
								int out_append);
int							check_tokens(t_token *tokens, t_data **data);
void						add_file_back(t_file **files, char *name,
								char *limiter, int out_append);
int							is_variable_env(char *str);
char						*ft_getenv(char *str, char **envp);

void						expand_tokens(t_data *data);
char						*expand_dollars(char *str, char **envp);
char						*replace_first_expandable(char *str, char **envp);
int							contains_expandables(char *str);
char						*var_to_replace(char *str);
char						*remove_quotes(char *str);
void						remove_quotes_tab(char **tab);

// Execution

void						exec_commands(t_data **data);
char						*get_path(char *str, char *envp[]);
int							get_heredocs(t_command **tab, t_data **data);
int							count_heredoc_per_command(t_file *file);
void						redirect_input(t_command *command, t_file *infile,
								int last);
void						apply_redirections(t_command *command,
								int pipe_fd[2]);
void						redirect_output(t_command *command,
								t_file *outfile);
void						close_heredocs_fd(t_command **commands);
int							count_commands_tab(t_command **tab);
int							done_in_parent(char *cmd);
int							get_exit_code(int exit_status);
void						is_a_directory(t_data **data, char *cmd);
void						reset_stdin_stdout(t_data **data);

// Builtins

void						ft_export_child(char **cmd, t_data **data);
void						ft_export_parent(char **cmd, t_data **data);
void						print_export(char **tab);
void						ft_cd(char **cmd, t_data **data);
void						ft_echo(char **cmd, t_data *data);
void						ft_pwd(t_data *data);
void						ft_unset(char **cmd, t_data **data);
void						ft_env(t_data *data);
void						ft_exit(char **cmd, t_data *data);
void						add_to_env(t_data **data, char *str);
void						update_env(t_data **data, char *str);
int							is_builtin_child(char **cmd, t_data *data);
int							is_builtin_parent(char **cmd, t_data *data);

// Debug

void						print_tokens(t_token *token);
void						print_command(t_command *command);
void						print_command_tab(t_command **tab);
void						print_files(t_file *file);
void						print_tab(char **tab);

// Error

void						lex_error(char *str, t_data **data);

// Signals

void						reset_signals(void);
void						setup_signals(void);
void						ignore_signals(void);
void						heredoc_signals(void);
void						handle_signals(int signum);
void						sigint_child(int signum);
void						sigint_heredoc(int signum);

#endif
