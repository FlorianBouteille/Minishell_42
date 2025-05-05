/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:37:03 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 16:35:43 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file_name, int option)
{
	int	fd;

	fd = 0;
	if (option == 0)
		fd = open(file_name, O_RDONLY, 0644);
	else if (option == 1)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (option == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error : no such file or rights on one of the file\n", 2);
	}
	return (fd);
}

void	redirect_all_inputs(t_command *command, int pipe_fd[2])
{
	t_file	*temp;
	int		number_heredoc;
	int		i;

	temp = command->infile;
	i = 0;
	number_heredoc = count_heredoc_per_command(command->infile);
	while (temp)
	{
		if (temp->limiter)
			i++;
		redirect_input(command, temp, number_heredoc - i);
		temp = temp->next;
	}
	close(pipe_fd[0]);
}

void	redirect_input(t_command *command, t_file *infile, int last)
{
	int	fd_in;

	if (infile->limiter)
	{
		if (last == 0)
		{
			if (dup2(command->fd_heredoc, STDIN_FILENO) == -1)
				perror("dup error in heredoc\n");
			// close(command->fd_heredoc);
		}
	}
	else if (infile->name)
	{
		// fprintf(stderr, "Je lis dans le infile : %s\n", infile->name);
		fd_in = open_file(infile->name, 0);
		if (fd_in == -1)
			command->skip_command = 1;
		else
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				perror("dup error");
			close(fd_in);
		}
	}
}

void	redirect_all_outputs(t_command *command, int pipe_fd[2])
{
	t_file	*temp;

	temp = command->outfile;
	if (!temp && command->index != command->number_commands - 1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup error");
	}
	while (temp)
	{
		redirect_output(temp);
		temp = temp->next;
	}
	close(pipe_fd[1]);
}

void	redirect_output(t_file *outfile)
{
	int	fd_out;

	if (outfile->name)
	{
		if (outfile->out_append)
			fd_out = open_file(outfile->name, 2);
		else
			fd_out = open_file(outfile->name, 1);
		if (fd_out == -1)
		{
			perror("no rights on the file\n");
			// free tous les trucs
			exit(0);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			perror("dup error");
		close(fd_out);
	}
}
