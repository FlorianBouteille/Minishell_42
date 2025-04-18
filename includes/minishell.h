/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:01:16 by csolari           #+#    #+#             */
/*   Updated: 2025/04/18 17:27:31 by csolari          ###   ########.fr       */
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
# include <unistd.h>

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

/// ^ boolean  (lib stdbool.h, bool ture false)
/// qui nous permette de savoir si faut expendre les dollars
/// entre single quote pas d expension (bool = false) entre double oui(bool = 1)

typedef struct s_command
{
	int				index;
	int				number_commands;
	int				out_append;
	char			*infile;
	char			*outfile;
	char			*limiter;
	int				fd_heredoc;
	char			*value;
}					t_command;

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

t_command			*new_command(t_token *tokens, int index,
						int number_commands);
t_command			**build_command_tab(t_token *tokens);
void				check_tokens(t_token *tokens);

// Execution

void				exec_commands(t_command **tab, char *envp[]);
char				*get_path(char *str, char *envp[]);
int					get_heredocs(t_command **tab);
void				redirect_input(t_command *command, int pipe_fd[2]);
void				redirect_output(t_command *command, int pipe_fd[2]);

// Debug

void				print_tokens(t_token *token);
void				print_command(t_command *command);
void				print_command_tab(t_command **tab);

// Error

void				lex_error(char *str, t_token **tokens);

#endif
