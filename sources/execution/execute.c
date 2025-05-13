/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:39:01 by csolari           #+#    #+#             */
/*   Updated: 2025/05/13 17:29:12 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *path, char **cmd, t_data **data)
{
	int	exit_code;

	exit_code = (*data)->exit_status;
	if (cmd && cmd[0] && done_in_parent(cmd[0]) == 1)
	{
		ft_free_tab((*data)->envp);
		free_all_data(data);
		exit(exit_code);
	}
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
	}
	else
	{
		is_a_directory(data, cmd[0]);
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
	reset_signals();
	redirect_all_inputs(command, pipe_fd);
	if (command->skip_command == 0)
		redirect_all_outputs(command, pipe_fd);
	close_heredocs_fd((*data)->commands);
	close((*data)->stdin_copy);
	close((*data)->stdout_copy);
	cmd = command->cmd_tab;
	if (command->skip_command)
	{
		ft_free_tab((*data)->envp);
		free_all_data(data);
		exit(1);
	}
	if (is_builtin_child(cmd, *data) != 0)
		exit(g_last_signal);
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

int	get_exit_code(int exit_status)
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
			return (0);
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
		return ;
	}
	(*data)->stdin_copy = dup(STDIN_FILENO);
	(*data)->stdout_copy = dup(STDOUT_FILENO);
	if ((*data)->number_of_commands == 1)
	{
		is_builtin_parent((*data)->commands[0]->cmd_tab, *data);
		g_last_signal = (*data)->exit_status;
	}
	while (i < (*data)->number_of_commands)
		exec_fork((*data)->commands[i++], data);
	while (wait(&(*data)->exit_status) > 0)
	{
		if ((*data)->commands[1]
			|| !done_in_parent((*data)->commands[0]->cmd_tab[0]))
			g_last_signal = get_exit_code((*data)->exit_status);
	}
	dup2((*data)->stdin_copy, STDIN_FILENO);
	close((*data)->stdin_copy);
	dup2((*data)->stdout_copy, STDOUT_FILENO);
	close((*data)->stdout_copy);
}

// printf("exits on %i\n", (*data)->exit_status);
// printf("so g_last_signal = %i\n", g_last_signal);
