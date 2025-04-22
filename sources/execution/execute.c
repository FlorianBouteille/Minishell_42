/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:39:01 by csolari           #+#    #+#             */
/*   Updated: 2025/04/22 17:06:51 by csolari          ###   ########.fr       */
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
		redirect_all_inputs(command, pipe_fd);
		redirect_all_outputs(command, pipe_fd);
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
	while (wait(NULL) > 0)
		;
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
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
