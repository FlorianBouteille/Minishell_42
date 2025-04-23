/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:39:01 by csolari           #+#    #+#             */
/*   Updated: 2025/04/23 16:36:09 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands_tab(t_command **tab)
{
	int	count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}
void	close_heredocs_fd(t_command **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		if (commands[i]->fd_heredoc != -1)
			close(commands[i]->fd_heredoc);
		i++;
	}
}
void	exec_child(t_command *command, char **envp)
{
	int		pipe_fd[2];
	int		pid;
	char	*path;
	char	**cmd;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	else if (pid == 0)
	{
		//sigaction.sa_handler = &fonctionpourlesenfants;
		redirect_all_inputs(command, pipe_fd);
		redirect_all_outputs(command, pipe_fd);
		
		//sigaction(SIGINT, lastructure, NULL)
		if (command->skip_command)
			exit(EXIT_FAILURE);
		cmd = ft_split(command->value, ' ');
		path = get_path(cmd[0], envp);
		execve(path, cmd, envp);
		perror("excve");
		free(path);
		ft_free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror("DuP ErOrRRe\n");
		close(pipe_fd[0]);
		if (command->fd_heredoc != -1)
			close(command->fd_heredoc);
	}
}

void	exec_commands(t_command **tab, char **envp)
{
	int	i;
	int	number_commands;
	int	number_heredoc;
	int	stdin_copy;
	int	stdout_copy;
	int	exit_status;

	exit_status = 0;
	number_commands = count_commands_tab(tab);
	i = 0;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	number_heredoc = get_heredocs(tab);
	while (i < number_commands)
	{
		exec_child(tab[i], envp);
		i++;
	}
	i = 0;
	while (wait(&exit_status) > 0)
		;
	//fprintf(stderr, "exit status = %i\n", exit_status);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
}


/*
ouvrir les fichiers de redirection s il y en a
creer pipe redirection
fork

execution
check commands patati patata
path


close
free
*/
