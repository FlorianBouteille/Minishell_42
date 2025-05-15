/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:17:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/15 11:20:46 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_command **command)
{
	(*command)->file = NULL;
	(*command)->value = NULL;
	(*command)->fd_heredoc = -1;
	(*command)->skip_command = 0;
	(*command)->stop_redir = 0;
	(*command)->cmd_tab = NULL;
	(*command)->number_commands = 0;
	(*command)->index = -1;
}

char	*add_token_to_command(t_token *tokens, t_command *command,
		int *condition_next, char *cmd_string)
{
	if (tokens->type == TOKEN_REDIR_IN && tokens->next
		&& tokens->next->type == TOKEN_WORD)
		add_file_back(&command->file, ft_strdup(tokens->next->value), NULL,
			IN);
	else if (tokens->type == TOKEN_REDIR_OUT && tokens->next
		&& tokens->next->type == TOKEN_WORD)
		add_file_back(&command->file, ft_strdup(tokens->next->value), NULL,
			OUT);
	else if (tokens->type == TOKEN_HEREDOC && tokens->next
		&& tokens->next->type == TOKEN_WORD)
		add_file_back(&command->file, NULL, ft_strdup(tokens->next->value),
			HEREDOC);
	else if (tokens->type == TOKEN_APPEND && tokens->next
		&& tokens->next->type == TOKEN_WORD)
		add_file_back(&command->file, ft_strdup(tokens->next->value), NULL,
			OUT_APPEND);
	else if (tokens->type == TOKEN_WORD)
	{
		*condition_next = 0;
		cmd_string = ft_strjoin_free_sep(cmd_string, tokens->value, ' ');
	}
	else
		printf("ERROR PARSING\n");
	return (cmd_string);
}

void	fill_command(t_command *command, int index, int number_commands,
		char *cmd_string)
{
	command->index = index;
	command->number_commands = number_commands;
	command->value = cmd_string;
	if (!command->value || ft_strlen(command->value) == 0)
		command->skip_command = 1;
	if (command->skip_command == 0)
		command->cmd_tab = ft_split_space_quote(command->value);
	if (command->cmd_tab)
		remove_quotes_tab(command->cmd_tab);
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
		cmd_string = add_token_to_command(tokens, command, &condition_next,
				cmd_string);
		if (condition_next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	fill_command(command, index, number_commands, cmd_string);
	return (command);
}
