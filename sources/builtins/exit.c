/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:14:54 by csolari           #+#    #+#             */
/*   Updated: 2025/05/02 13:00:02 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_data *data)
{
	if (cmd[1])
		ft_putstr_fd("exit : doesn't require arguments\n", 2);
	ft_free_tab(data->envp);
	free_all_data(&data);
	exit(EXIT_SUCCESS);
}