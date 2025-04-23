/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:37 by csolari           #+#    #+#             */
/*   Updated: 2025/04/23 15:34:17 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_signal = 0;

void	say_hi(int signum)
{
	if (signum == SIGINT)
		fprintf(stderr, "J'ai recu un ctrl + c !!\n");
	else
		fprintf(stderr, "j'ai recu un autre signal\n");
	last_signal = signum;
}

int	minishell(char **envp)
{
	char		*line;
	t_token		*tokens;
	t_command	**tab;

	tokens = NULL;
	tab = NULL;
	while (1)
	{
		// check ctrl + backslash
		line = readline("ya quoi ? > ");
		if (!line)
			return (0); //exit proprement
		//check ctrl + c
		add_history(line);
		line = add_spaces(line);
		tokens = lex_string(line);
		check_tokens(tokens);
	//	print_tokens(tokens);
		tab = build_command_tab(tokens);
		//print_command_tab(tab);
		exec_commands(tab, envp);
		free_tokens(&tokens);
		free_command_tab(tab);
	}
	// rl_clear_history();
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1)
		return (printf("Minishell needs no arguments \n"), 1);

	//sigaction(SIGINT, say_hi, NULL);
	(void)argv;
	minishell(envp);
	return (0);
}
