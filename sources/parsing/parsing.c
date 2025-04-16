/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:17:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/16 15:28:07 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_command **command)
{
	(*command)->infile = NULL;
	(*command)->outfile = NULL;
	(*command)->value = NULL;
	(*command)->limiter = NULL;
	(*command)->out_append = 0;
}

t_command	*new_command(t_token *tokens)
{
	t_command	*command;
	char		*cmd_string;

	cmd_string = NULL;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(&command);
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_REDIR_IN && tokens->next && tokens->next->type == TOKEN_WORD )
		{
			command->infile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_REDIR_OUT && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			command->outfile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_HEREDOC  && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			command->infile = ft_strdup("heredoc");
			command->limiter = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_APPEND  && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			command->outfile = ft_strdup(tokens->next->value);
			command->out_append = 1;
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_WORD)
		{
			cmd_string = ft_strjoin_free(cmd_string, tokens->value);
		}
		else
			printf("ERROR PARSING\n");
		tokens = tokens->next;
	}
	command->value = cmd_string;
	return (command);
}

// int		count_pipe(t_token )





