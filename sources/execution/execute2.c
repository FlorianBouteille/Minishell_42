/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:07:06 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 16:25:46 by csolari          ###   ########.fr       */
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

int	done_in_parent(char *cmd)
{
	int		len_cmd;

	if (!cmd)
		return (0);
	len_cmd = ft_strlen(cmd);
	if (ft_strncmp(cmd, "export", len_cmd) == 0 && len_cmd == 6)
		return (1);
	else if (ft_strncmp(cmd, "cd", len_cmd) == 0 && len_cmd == 2)
		return (1);
	else if (ft_strncmp(cmd, "unset", len_cmd) == 0 && len_cmd == 5)
		return (1);
	else if (ft_strncmp(cmd, "exit", len_cmd) == 0 && len_cmd == 4)
		return (1);
	return (0);
}
