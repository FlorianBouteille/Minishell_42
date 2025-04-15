/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:01:16 by csolari           #+#    #+#             */
/*   Updated: 2025/04/15 11:01:45 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
} t_token;

typedef struct s_command
{
	int		out_append;
	char	*infile;
	char 	*outfile;
	char	*limiter;
	char	*value;
}	t_command;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_END
}	t_token_type;

//Lexing

t_token	*lex_string(char *str);
void	add_token(char *str, t_token **tokens);
t_token	*new_token(char *str);
int		get_word_len(char *str);
char	*make_word(char *str);
void	free_tokens(t_token **tokens);

// Parsing

t_command	*new_command(t_token *tokens);

//Debug

void	print_tokens(t_token *token);
void	print_command(t_command *command);

#endif
