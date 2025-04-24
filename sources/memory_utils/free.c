/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:58:59 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/22 13:56:21 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_data(t_data **data)
{
	if (!(*data))
		return ;
	if ((*data)->tokens)
		free_tokens(&(*data)->tokens);
	if ((*data)->commands)
		free_command_tab((*data)->commands);
	free(*data);
	*data = NULL;
}

void	free_file_list(t_file *list)
{
	t_file	*temp;

	temp = list;
	if (!list)
		return ;
	while (temp)
	{
		temp = temp->next;
		if (list->name)
			free(list->name);
		if (list->limiter)
			free(list->limiter);
		free(list);
		list = temp;
	}
}

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
		free_file_list(command->infile);
	if (command->outfile)
		free_file_list(command->outfile);
	if (command->value)
		free(command->value);
	free(command);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_command_tab(t_command **tab)
{
	int	i;

	i = 0;
	if (!tab || !(*tab))
		return ;
	while (tab[i])
	{
		free_command(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
}
