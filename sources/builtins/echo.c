/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:17 by csolari           #+#    #+#             */
/*   Updated: 2025/05/02 15:34:39 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd, t_data *data)
{
	int	n_condition;
	int	i;

	i = 1;
	n_condition = 1;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(cmd[1], "-n", 2) == 0 && ft_strlen(cmd[1]) == 2)
	{
		n_condition = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_condition)
		ft_putstr_fd("\n", 1);
	free_all_data(&data);
	exit(EXIT_SUCCESS);
}
