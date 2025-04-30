/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:39:01 by csolari           #+#    #+#             */
/*   Updated: 2025/04/30 14:11:57 by csolari          ###   ########.fr       */
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
void	exec_child(t_command *command, t_data **data)
{
	int		pipe_fd[2];
	int		pid;
	char	*path;
	char	**cmd;

	pipe(pipe_fd);
	pid = fork();
	cmd = NULL;
	path = NULL;
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	else if (pid == 0)
	{
		// sigaction.sa_handler = &fonctionpourlesenfants;
		redirect_all_inputs(command, pipe_fd);
		redirect_all_outputs(command, pipe_fd);
		// sigaction(SIGINT, lastructure, NULL)
		close_heredocs_fd((*data)->commands);
		close((*data)->stdin_copy);
		close((*data)->stdout_copy);
		if (command->skip_command)
		{
			free_all_data(data);
			exit(EXIT_FAILURE);
		}
		cmd = command->cmd_tab;
		if (is_builtin_child(cmd, *data) != 0)
			exit(EXIT_SUCCESS);
		path = get_path(cmd[0], (*data)->envp);
		if (path)
		{
			execve(path, cmd, (*data)->envp);
			perror("execve");
		}
		free_all_data(data);
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror("dup2 error");
		close(pipe_fd[0]);
		if (command->fd_heredoc != -1)
			close(command->fd_heredoc);
	}
}

void	exec_commands(t_data **data)
{
	int	i;

	i = 0;
	(*data)->number_of_commands = count_commands_tab((*data)->commands);
	(*data)->number_heredoc = get_heredocs((*data)->commands, data);
	(*data)->stdin_copy = dup(STDIN_FILENO);
	(*data)->stdout_copy = dup(STDOUT_FILENO);
	if ((*data)->number_of_commands == 1 )//&& is_parent_builtin((*data)->commands->cmd_tab[0]))
	{
		is_builtin_parent((*data)->commands[0]->cmd_tab, *data);
	}
	while (i < (*data)->number_of_commands)
	{
		exec_child((*data)->commands[i], data);
		i++;
	}
	i = 0;
	while (wait(&(*data)->exit_status) > 0)
		;
	// fprintf(stderr, "exit status = %i\n", exit_status);
	dup2((*data)->stdin_copy, STDIN_FILENO);
	close((*data)->stdin_copy);
	dup2((*data)->stdout_copy, STDOUT_FILENO);
	close((*data)->stdout_copy);
}

