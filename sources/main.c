/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:37 by csolari           #+#    #+#             */
/*   Updated: 2025/04/16 15:58:49 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(void)
{
	char	*line;
	t_token	*tokens;
	t_command	*command;

	tokens = NULL;
	while (1)
	{
		line = readline("ya quoi ? > ");
		if (!line)
			return (0);
		line = add_spaces(line);
		printf("line with spaces = %s\n", line);
		tokens = lex_string(line);
		print_tokens(tokens);
		if(!check_tokens(tokens))
			printf("pb de format near <<>> \n");
		command = new_command(tokens);
		print_command(command);
		add_history(line);
		free(line);
		free_tokens(&tokens);
		free_command(command);
		tokens = NULL;
	}
	return (1);
}

int main(void)
{
	minishell();
	return(0);
}
