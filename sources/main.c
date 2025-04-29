/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:37 by csolari           #+#    #+#             */
/*   Updated: 2025/04/29 17:40:04 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		last_signal = 0;

void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!data)
		return ;
	(*data)->number_of_commands = 0;
	(*data)->number_heredoc = 0;
	(*data)->stdin_copy = -1;
	(*data)->stdout_copy = -1;
	(*data)->exit_status = 0;
	(*data)->tokens = NULL;
	(*data)->commands = NULL;
	if (!(*data)->envp)
		(*data)->envp = copy_tab(envp);
}

int	minishell(char **envp)
{
	char	*line;
	t_data	*data;

	data = NULL;
	while (1)
	{
		init_data(&data, envp);
		// check ctrl + backslash
		line = readline("ya quoi ? > ");
		if (!line)
			return (free_all_data(&data), 0); // exit proprement
		// check ctrl + c
		add_history(line);
		line = add_spaces(line);
		data->tokens = lex_string(line);
		if (!check_tokens(data->tokens, &data))
			continue ;
		data->commands = build_command_tab(data);
		print_command_tab(data->commands);
		exec_commands(&data);
		free_all_data(&data);
	}
	// rl_clear_history();
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1)
		return (printf("Minishell needs no arguments \n"), 1);
	// sigaction(SIGINT, say_hi, NULL);
	(void)argv;
	minishell(envp);
	return (0);
}

// fonction get data qui va interroger la static et la renvoie
// variable globale simulee
// va chercher la variable persistante

// foncton qui initiise set le pointeur static
// une qui get

// sigaction pour les infos du signal pid et tt ca