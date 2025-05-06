/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:17 by csolari           #+#    #+#             */
/*   Updated: 2025/05/06 16:25:26 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_no_args(t_data *data)
{
	ft_putstr_fd("\n", 1);
	ft_free_tab(data->envp);
	free_all_data(&data);
	exit(EXIT_SUCCESS);
}

void	ft_echo(char **cmd, t_data *data)
{
	int	n_condition;
	int	i;

	i = 1;
	n_condition = 1;
	if (!cmd[1])
		echo_no_args(data);
	if (ft_strncmp(cmd[1], "-n", 2) == 0 && ft_strlen(cmd[1]) == 2)
	{
		n_condition = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_condition)
		ft_putstr_fd("\n", 1);
	ft_free_tab(data->envp);
	free_all_data(&data);
	exit(EXIT_SUCCESS);
}
