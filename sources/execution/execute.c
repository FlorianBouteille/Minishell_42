/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:39:01 by csolari           #+#    #+#             */
/*   Updated: 2025/04/17 15:30:31 by csolari          ###   ########.fr       */
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

int	open_file(t_command *command, int option)
{
	int	fd;

	fd = 0;
	if (option == 0)
		fd = open(command->infile, O_RDONLY, 0644);
	else if (option == 1)
		fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (option == 2)
		fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error : no such file or rights on one of the file ", 2); ///A CHANGER
		// ft_putendl_fd(, 2);
	}
	return (fd);
}

void	redirect_input(t_command *command, int pipe_fd[2])
{
	int	fd_in;

	if (command->infile)
	{
		fd_in = open_file(command, 0);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			perror("dup error");
		close(fd_in);
	}
	else if (command->index != 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			printf("ici0\n");
			perror("dup error");
		}
	}
	close(pipe_fd[0]);
	
}

void	redirect_output(t_command *command, int pipe_fd[2])
{
	int	fd_out;


	if (command->outfile)
	{
		fd_out = open_file(command, 1);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			printf("ici1\n");
			perror("dup error");
		}
		close(fd_out);
	}
	else if (command->index != command->number_commands - 1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			printf("ici2\n");
			perror("dup error");
		}
	}
	close(pipe_fd[1]);
}

void	exec_child(t_command *command, char **envp)
{
	int		pipe_fd[2];
	int		pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		//pid_error;
		return ;
	}
	else if (pid == 0)
	{
		redirect_input(command, pipe_fd);
		redirect_output(command, pipe_fd);
		char **cmd = ft_split(command->value, ' ');
		execve(cmd[0], cmd, envp);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror("DuP ErOrRRe\n");
		close(pipe_fd[0]);
	}
}

void	exec_commands(t_command **tab, char **envp)
{
	int		i;
	int		number_commands;
	int		stdin_copy;
	int		stdout_copy;

	number_commands = count_commands_tab(tab);
	i = 0;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	while (i < number_commands)
	{
		exec_child(tab[i], envp);
		i++;
	}
	i = 0;
	while (i < number_commands)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
}