/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:37 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 11:52:02 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_signal = 0;

void	init_data(t_data **data, char **envp, char **envp_mem)
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
	(*data)->pid_tab = NULL;
	(*data)->envp = NULL;
	if (!envp_mem)
		(*data)->envp = copy_tab(envp);
	else
		(*data)->envp = envp_mem;
}

void	build_and_exec(t_data **data)
{	
	(*data)->commands = build_command_tab(*data);
	exec_commands(data);
}

int	minishell(char **envp)
{
	char	*line;
	t_data	*data;
	char	**envp_mem;

	data = NULL;
	envp_mem = NULL;
	while (1)
	{
		setup_signals();
		init_data(&data, envp, envp_mem);
		line = readline("Minishell > ");
		if (!line)
			return (ft_free_tab(data->envp), free_all_data(&data), 0);
		add_history(line);
		line = add_spaces(line);
		data->tokens = lex_string(line);
		if (data->tokens && check_tokens(data->tokens, &data))
			build_and_exec(&data);
		envp_mem = data->envp;
		data->envp = NULL;
		free_all_data(&data);
	}
	return (ft_free_tab(envp_mem), rl_clear_history(), 1);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1)
		return (printf("Minishell needs no arguments \n"), 1);
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
