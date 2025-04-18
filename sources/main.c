/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:37 by csolari           #+#    #+#             */
/*   Updated: 2025/04/18 15:43:42 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **envp)
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
		tokens = lex_string(line);
	//	print_tokens(tokens);
		check_tokens(tokens);
		tab = build_command_tab(tokens);
	//	print_command_tab(tab);
		exec_commands(tab, envp);
		free_tokens(&tokens);
		free_command_tab(tab);
	}
	
	//rl_clear_history();
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	if (argc > 1)
		return (printf("Minishell needs no arguments \n"), 1);
	(void)argv;
	minishell(envp);
	return(0);
}
