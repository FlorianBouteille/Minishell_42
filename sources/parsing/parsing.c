/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:17:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/06 12:03:18 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_command **command)
{
	(*command)->infile = NULL;
	(*command)->outfile = NULL;
	(*command)->value = NULL;
	(*command)->fd_heredoc = -1;
	(*command)->skip_command = 0;
	(*command)->number_commands = 0;
	(*command)->index = -1;
}

t_command	*new_command(t_token *tokens, int index, int number_commands)
{
	t_command	*command;
	char		*cmd_string;
	int			condition_next;

	cmd_string = NULL;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(&command);
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		condition_next = 1;
		if (tokens->type == TOKEN_REDIR_IN && tokens->next
			&& tokens->next->type == TOKEN_WORD)
			add_file_back(&command->infile, ft_strdup(tokens->next->value),
				NULL, 0);
		else if (tokens->type == TOKEN_REDIR_OUT && tokens->next
			&& tokens->next->type == TOKEN_WORD)
			add_file_back(&command->outfile, ft_strdup(tokens->next->value),
				NULL, 0);
		else if (tokens->type == TOKEN_HEREDOC && tokens->next
			&& tokens->next->type == TOKEN_WORD)
			add_file_back(&command->infile, NULL,
				ft_strdup(tokens->next->value), 0);
		else if (tokens->type == TOKEN_APPEND && tokens->next
			&& tokens->next->type == TOKEN_WORD)
			add_file_back(&command->outfile, ft_strdup(tokens->next->value),
				NULL, 1);
		else if (tokens->type == TOKEN_WORD)
		{
			condition_next = 0;
			cmd_string = ft_strjoin_free_sep(cmd_string, tokens->value, ' ');
		}
		else
			printf("ERROR PARSING\n");
		if (condition_next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	command->index = index;
	command->number_commands = number_commands;
	command->value = cmd_string;
	command->cmd_tab = ft_split_space_quote(command->value);
	if (!command->cmd_tab)
		ft_free_tab(command->cmd_tab);
	remove_quotes_tab(command->cmd_tab);
	if (!command->value || ft_strlen(command->value) == 0)
		command->skip_command = 1;
	return (command);
}
