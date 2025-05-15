/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:14:54 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 12:36:08 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **cmd, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd[1] && is_numeric(cmd[1]) && cmd[2])
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		exit_code = 1;
		return ;
	}
	else if (cmd[1] && !is_numeric(cmd[1]))
	{
		ft_putstr_fd("exit : ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (cmd[1] && is_numeric(cmd[1]) && !cmd[2])
		exit_code = ft_atoi(cmd[1]) % 256;
	ft_free_tab(data->envp);
	free_all_data(&data);
	g_last_signal = exit_code;
	exit(exit_code);
}
