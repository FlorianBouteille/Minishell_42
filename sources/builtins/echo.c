/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:17 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 12:36:16 by csolari          ###   ########.fr       */
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

int	get_n_conditon(char **cmd, int *i)
{
	int	break_c;
	int	n_condition;
	int	j;

	n_condition = 1;
	break_c = 0;
	while (cmd[*i] && cmd[*i][0] == '-' && cmd[*i][1] == 'n' && break_c == 0)
	{
		j = 2;
		while (cmd[*i][j])
		{
			if (cmd[*i][j] == 'n')
				j++;
			else
			{
				break_c = 1;
				break ;
			}
		}
		if (break_c == 0)
			(*i)++;
	}
	if (*i > 1)
		n_condition = 0;
	return (n_condition);
}

void	ft_echo(char **cmd, t_data *data)
{
	int	n_condition;
	int	i;

	i = 1;
	if (!cmd[1])
		echo_no_args(data);
	n_condition = get_n_conditon(cmd, &i);
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
