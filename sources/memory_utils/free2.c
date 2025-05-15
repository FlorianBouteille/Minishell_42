/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:43:22 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 11:38:38 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->file)
		free_file_list(command->file);
	if (command->value)
		free(command->value);
	if (command->cmd_tab)
		ft_free_tab(command->cmd_tab);
	free(command);
}

void	free_command_tab(t_command **tab)
{
	int	i;

	i = 0;
	if (!tab || !(*tab))
		return ;
	while (tab && tab[i])
	{
		free_command(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
}
