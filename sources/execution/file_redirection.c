/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:37:03 by csolari           #+#    #+#             */
/*   Updated: 2025/04/18 17:26:00 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd("error : no such file or rights on one of the file ", 2);
		/// A CHANGER
		// ft_putendl_fd(, 2);
	}
	return (fd);
}

void	redirect_input(t_command *command, int pipe_fd[2])
{
	int	fd_in;

	if (command->fd_heredoc != -1)
	{
		fprintf(stderr, "Je lis dans le fd_heredoc = %i\n",
			command->fd_heredoc);
		if (dup2(command->fd_heredoc, STDIN_FILENO) == -1)
			perror("dup error");
		close(command->fd_heredoc);
	}
	else if (command->infile)
	{
		fprintf(stderr, "Je lis dans le infile : %s\n", command->infile);
		fd_in = open_file(command, 0);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			perror("dup error");
		close(fd_in);
	}
	close(pipe_fd[0]);
}

void	redirect_output(t_command *command, int pipe_fd[2])
{
	int	fd_out;

	if (command->outfile)
	{
		if (command->out_append)
			fd_out = open_file(command, 2);
		else
			fd_out = open_file(command, 1);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			perror("dup error");
		close(fd_out);
	}
	else if (command->index != command->number_commands - 1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup error");
	}
	close(pipe_fd[1]);
}
