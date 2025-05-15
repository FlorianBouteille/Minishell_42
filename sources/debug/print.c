/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:22:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/15 12:34:31 by csolari          ###   ########.fr       */
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
	int		i;
	t_file	*temp;

	i = 0;
	temp = file;
	if (!file)
	{
		printf("No files found\n");
		return ;
	}
	while (temp)
	{
		printf("file %i\n", i);
		printf("name = %s\n", temp->name);
		printf("limiter = %s\n", temp->limiter);
		if (temp->type == OUT_APPEND)
			printf("je dois append\n");
		temp = temp->next;
		i++;
	}
}

void	print_command(t_command *command)
{
	printf("infiles = \n");
	print_files(command->file);
	if (!command->value)
	{
		printf("pb affichage, pas de commande\n");
		return ;
	}
	printf("command and args = %s\n\n", command->value);
	printf("heredoc = %i\n", command->fd_heredoc);
}

void	print_command_tab(t_command **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[i])
	{
		printf("pb affichage, pas de commandes\n");
		return ;
	}
	printf("LES COMMMANDES :\n");
	while (tab[i])
	{
		printf("\ncommande %i\n", i + 1);
		print_command(tab[i]);
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	while (tab[i])
	{
		ft_putstr_fd(tab[i++], 1);
		ft_putstr_fd("\n", 1);
	}
}
