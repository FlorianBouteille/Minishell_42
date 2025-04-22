/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:37:03 by csolari           #+#    #+#             */
/*   Updated: 2025/04/22 17:13:54 by csolari          ###   ########.fr       */
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

int	count_heredoc_per_command(t_file *file)
{
	int		count;
	t_file	*temp;

	count = 0;
	temp = file;
	while(temp)
	{
		if (temp->limiter)
			count++;
		temp = temp->next;
	}
	return (count);
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
		redirect_input(command, temp, pipe_fd, number_heredoc - i);
		temp = temp->next;
	}
}


void	redirect_input(t_command *command, t_file *infile, int pipe_fd[2], int last)
{
	int	fd_in;

	if (infile->limiter)
	{
		if (last == 0)
		{
			fprintf(stderr, "Je lis dans le fd_heredoc = %i\n", command->fd_heredoc);
			if (dup2(command->fd_heredoc, STDIN_FILENO) == -1)
				perror("dup errorhkef2	 goifht	");
			close(command->fd_heredoc);
		}
	}
	else if (infile->name)
	{
		fprintf(stderr, "Je lis dans le infile : %s\n", infile->name);
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
	if (infile->next == NULL)
		close(pipe_fd[0]);
}

void	redirect_all_outputs(t_command *command, int pipe_fd[2])
{
	t_file	*temp;

	temp = command->outfile;
	while (temp)
	{
		redirect_output(command, temp, pipe_fd);
		temp = temp->next;
	}

}

void	redirect_output(t_command *command, t_file *outfile, int pipe_fd[2])
{
	int	fd_out;

	if (outfile)
	{
		if (outfile->out_append)
			fd_out = open_file(outfile->name, 2);
		else
			fd_out = open_file(outfile->name, 1);
		if (fd_out == -1)
		{
			perror("no rights on the file\n");
			//free tous les trucs
			exit(0);
		}
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
