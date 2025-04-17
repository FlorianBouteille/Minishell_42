/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:53:11 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/17 15:11:50 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_token *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			count++;
		tokens = tokens->next;
	}
	printf("count == %i\n", count);
	return (count);
}

t_command	**build_command_tab(t_token *tokens)
{
	int			number_of_commands;
	int			i;
	t_command	**tab;
	t_token		*tmp;

	i = 0;
	number_of_commands = count_commands(tokens);
	tab = malloc((number_of_commands + 1) * sizeof(t_command));
	if (!tab)
		return (NULL);
	tmp = tokens;
	while (i < number_of_commands)
	{
		tab[i] = new_command(tmp, i, number_of_commands);
		while (tmp && tmp->next && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->next && tmp->type == TOKEN_PIPE)
			tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
