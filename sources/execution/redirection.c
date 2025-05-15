/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:25:56 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/15 12:46:40 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_outfile(t_file *file)
{
	t_file	*temp;
	int		count;

	count = 0;
	temp = file;
	while (temp)
	{
		if (temp->type == OUT || temp->type == OUT_APPEND)
			count++;
		temp = temp->next;
	}
	return (count);
}

void	close_both_pipes(int pipe_fd[2])
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

void	apply_redirections(t_command *command, int pipe_fd[2])
{
	t_file	*temp;
	int		number_heredoc;
	int		i;

	i = 0;
	temp = command->file;
	if (!nbr_outfile(temp) && command->index != command->number_commands - 1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup error");
	}
	number_heredoc = count_heredoc_per_command(command->file);
	while (temp && command->stop_redir == 0)
	{
		if (temp->type == HEREDOC)
			i++;
		if (temp->type == IN || temp->type == HEREDOC)
			redirect_input(command, temp, number_heredoc - i);
		else if (temp->type == OUT || temp->type == OUT_APPEND)
			redirect_output(command, temp);
		temp = temp->next;
	}
	if (command->skip_command != 1)
		command->skip_command = command->stop_redir;
	close_both_pipes(pipe_fd);
}
