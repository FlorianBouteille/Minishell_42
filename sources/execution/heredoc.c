/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:34:40 by csolari           #+#    #+#             */
/*   Updated: 2025/05/13 10:22:18 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredoc_per_command(t_file *file)
{
	int		count;
	t_file	*temp;

	count = 0;
	temp = file;
	while (temp)
	{
		if (temp->limiter)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	is_limiter(char *str, char *limiter)
{
	int	len_limiter;
	int	i;

	i = 0;
	len_limiter = ft_strlen(limiter);
	if (!str || !limiter)
		return (0);
	if (len_limiter != (int)ft_strlen(str))
		return (0);
	while (i < len_limiter)
	{
		if (str[i] != 0 && limiter[i] != 0 && str[i] != limiter[i])
			return (0);
		i++;
	}
	return (1);
}

void	heredoc_child(t_data **data, t_file *file, int fd[2])
{
	char	*line;

	heredoc_signals();
	close_heredocs_fd((*data)->commands);
	while (1)
	{
		line = readline("heredoc > ");
		if (!line || (is_limiter(line, file->limiter) == 1))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	close(fd[0]);
	ft_free_tab((*data)->envp);
	free_all_data(data);
	exit(g_last_signal);
}

int	heredoc(t_data **data, t_command *tab, t_file *file)
{
	int		fd[2];
	int		pid;
	int		signal;

	signal = 0;
	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("pid error");
	else if (pid == 0)
		heredoc_child(data, file, fd);
	else
	{
		close(fd[1]);
		if (tab->fd_heredoc > 0)
			close(tab->fd_heredoc);
		tab->fd_heredoc = fd[0];
		wait(&(*data)->exit_status);
		signal = get_exit_code((*data)->exit_status);
		if (signal != 0 && tab->fd_heredoc != -1)
			close(tab->fd_heredoc);
	}
	return (signal);
}

int	get_heredocs(t_command **tab, t_data **data)
{
	int		i;
	t_file	*temp;
	int		signal;

	i = 0;
	signal = 0;
	g_last_signal = 0;
	while (tab[i] && g_last_signal == 0)
	{
		temp = tab[i]->file;
		while (temp && g_last_signal == 0)
		{
			if (temp->limiter)
			{
				signal = heredoc(data, tab[i], temp);
				if (signal != 0)
					return (signal);
			}
			temp = temp->next;
		}
		i++;
	}
	return (signal);
}
