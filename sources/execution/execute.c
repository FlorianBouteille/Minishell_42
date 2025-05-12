/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:39:01 by csolari           #+#    #+#             */
/*   Updated: 2025/05/07 14:41:21 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *path, char **cmd, t_data **data)
{
	if (done_in_parent(cmd[0]) == 1)
	{
		ft_free_tab((*data)->envp);
		free_all_data(data);
		exit(EXIT_SUCCESS);
	}
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : command not found !\n", 2);
	}
	else
	{
		execve(path, cmd, (*data)->envp);
		perror("execve");
	}
	ft_free_tab((*data)->envp);
	free_all_data(data);
	free(path);
	exit(127);
}

void	exec_child(t_command *command, t_data **data, int pipe_fd[2])
{
	char	*path;
	char	**cmd;

	path = NULL;
	cmd = NULL;
	// sigaction.sa_handler = &fonctionpourlesenfants;
	reset_signals();
	redirect_all_inputs(command, pipe_fd);
	redirect_all_outputs(command, pipe_fd);
	// sigaction(SIGINT, lastructure, NULL)
	close_heredocs_fd((*data)->commands);
	close((*data)->stdin_copy);
	close((*data)->stdout_copy);
	cmd = command->cmd_tab;
	if (is_builtin_child(cmd, *data) != 0)
		exit(g_last_signal);
	if (command->skip_command)
	{
		ft_free_tab((*data)->envp);
		free_all_data(data);
		exit(EXIT_FAILURE);
	}
	path = get_path(cmd[0], (*data)->envp);
	execute(path, cmd, data);
}

void	exec_fork(t_command *command, t_data **data)
{
	int	pipe_fd[2];
	int	pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	else if (pid == 0)
		exec_child(command, data, pipe_fd);
	else
	{
		ignore_signals();
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror("dup2 error");
		close(pipe_fd[0]);
		if (command->fd_heredoc != -1)
			close(command->fd_heredoc);
	}
}

int		get_exit_code(int exit_status)
{
	int	signal;

	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
	{
		signal = WTERMSIG(exit_status);
		if (signal == SIGSYS)
			return (127);
		if (signal == SIGPIPE)
			return (127);
		return (128 + signal);
	}
	return (0);
}

void	exec_commands(t_data **data)
{
	int	i;

	i = 0;
	ignore_signals();
	(*data)->number_of_commands = count_commands_tab((*data)->commands);
	(*data)->number_heredoc = get_heredocs((*data)->commands, data);
	if (WIFSIGNALED((*data)->number_heredoc))
	{
		g_last_signal = 130;
		// close_heredocs_fd((*data)->commands);
		return ;
	}
	(*data)->stdin_copy = dup(STDIN_FILENO);
	(*data)->stdout_copy = dup(STDOUT_FILENO);
	if ((*data)->number_of_commands == 1)
		is_builtin_parent((*data)->commands[0]->cmd_tab, *data);
	while (i < (*data)->number_of_commands)
	{
		exec_fork((*data)->commands[i], data);
		i++;
	}
	i = 0;
	while (wait(&(*data)->exit_status) > 0)
	{
		printf("exits on %i\n", (*data)->exit_status);
		g_last_signal = get_exit_code((*data)->exit_status);
		printf("so g_last_signal = %i\n", g_last_signal);
	}
	dup2((*data)->stdin_copy, STDIN_FILENO);
	close((*data)->stdin_copy);
	dup2((*data)->stdout_copy, STDOUT_FILENO);
	close((*data)->stdout_copy);
}
