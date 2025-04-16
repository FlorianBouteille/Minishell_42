/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:58:59 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/16 15:47:10 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	
	if (!(*tokens))
		return ;
	tmp = *tokens;
	while (tmp)
	{
		tmp = tmp->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->infile)
		free(command->infile);
	if (command->outfile)
		free(command->outfile);
	if (command->limiter)
		free(command->limiter);
	if (command->value)
		free(command->value);
	free(command);
}

void	free_command_tab(t_command **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free_command(tab[i]);
		i++;
	}
	free(tab);
}
