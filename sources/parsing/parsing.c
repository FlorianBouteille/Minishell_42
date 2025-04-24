/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:17:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/24 14:44:35 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_command **command)
{
	(*command)->infile = NULL;
	(*command)->outfile = NULL;
	(*command)->value = NULL;
	//(*command)->limiter = NULL;
	(*command)->fd_heredoc = -1;
	(*command)->skip_command = 0;
	(*command)->number_commands = 0;
	//(*command)->out_append = 0;
	(*command)->index = -1;
}

t_command	*new_command(t_token *tokens, int index, int number_commands)
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
		if (tokens->type == TOKEN_REDIR_IN && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			add_file_back(&command->infile, ft_strdup(tokens->next->value), NULL, 0);		
			//command->infile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_REDIR_OUT && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			add_file_back(&command->outfile, ft_strdup(tokens->next->value), NULL, 0);		
			//command->outfile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_HEREDOC  && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			add_file_back(&command->infile, NULL, ft_strdup(tokens->next->value), 0);		
			//command->limiter = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_APPEND  && tokens->next && tokens->next->type == TOKEN_WORD)
		{
			add_file_back(&command->outfile, ft_strdup(tokens->next->value), NULL, 1);		
			//command->outfile = ft_strdup(tokens->next->value);
			//command->out_append = 1;
			tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_WORD)
		{
			cmd_string = ft_strjoin_free_sep(cmd_string, tokens->value, ' ');
			//printf("cmd_string = %s\n", cmd_string);
		}
		else
			printf("ERROR PARSING\n");
		tokens = tokens->next;
	}
	command->index = index;
	command->number_commands = number_commands;
	command->value = cmd_string;
	if (!command->value || ft_strlen(command->value) == 0)
		command->skip_command = 1;
	return (command);
}

// int		count_pipe(t_token )





