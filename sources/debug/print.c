/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:22:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/16 15:26:17 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens)
	{
		printf("____________\n");
		printf("token number %i\n", i);
		printf("value = %s\n", tokens->value);
		printf("type = %i\n", tokens->type);
		printf("____________\n\n");
		tokens = tokens->next;
		i++;
	}
}

void	print_files(t_file *file)
{
	int	i;

	i = 0;
	if (!file)
	{
		printf("No files found\n");
		return ;
	}
	while (file)
	{
		printf("file %i\n", i);
		printf("name = %s\n", file->name);
		printf("limiter = %s\n", file->limiter);
		if (file->out_append)
			printf("je dois append\n");
		file = file->next;
		i++;
	}
}

void	print_command(t_command *command)
{
	printf("infiles = \n");
	print_files(command->infile);
	//printf("outfiles = \n");
	//print_files(command->outfile);
	printf("command and args = %s\n\n", command->value);
	printf("heredoc = %i\n", command->fd_heredoc);
}

void	print_command_tab(t_command **tab)
{
	int	i;

	i = 0;
	printf("LES COMMMANDES :\n");
	while (tab[i])
	{
		printf("\ncommande %i\n", i + 1);
		print_command(tab[i]);
		i++;
	}
}
