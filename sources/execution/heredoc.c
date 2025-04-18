/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:34:40 by csolari           #+#    #+#             */
/*   Updated: 2025/04/18 17:26:03 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	heredoc(t_command *tab)
{
	char	*line;
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("pid error");
	else if (pid == 0)
	{
		while (1)
		{
			line = readline("heredoc > ");
			if (!line || (is_limiter(line, tab->limiter) == 1))
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
		exit(0);
	}
	else
	{
		close(fd[1]);
		tab->fd_heredoc = fd[0];
		// dup(fd[0]);
		// close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	get_heredocs(t_command **tab)
{
	int	i;
	int	number_heredoc;

	i = 0;
	number_heredoc = 0;
	while (tab[i])
	{
		if (tab[i]->limiter)
		{
			heredoc(tab[i]);
			number_heredoc++;
		}
		i++;
	}
	return (number_heredoc);
}
