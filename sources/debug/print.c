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

void	print_command(t_command *command)
{
	printf("j'essaye d'imprimer les commandes\n");
	printf("infile = %s\n", command->infile);
	printf("outfile = %s\n", command->outfile);
	printf("limiter = %s\n", command->limiter);
	if (command->out_append)
		printf("Je dois append\n");	
	printf("command and args = %s\n\n", command->value);
}
