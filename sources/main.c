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
	t_command	**tab;

	tokens = NULL;
	while (1)
	{
		line = readline("ya quoi ? > ");
		if (!line)
			return (0);
		add_history(line);
		line = add_spaces(line);
		printf("line with spaces = %s\n", line);
		tokens = lex_string(line);
		print_tokens(tokens);
		check_tokens(tokens);
		tab = build_command_tab(tokens);
		print_command_tab(tab);
		free_tokens(&tokens);
		free_command_tab(tab);
	}
	return (1);
}

int main(void)
{
	minishell();
	return(0);
}
