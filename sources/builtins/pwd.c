/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:14:33 by csolari           #+#    #+#             */
/*   Updated: 2025/04/30 14:19:58 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_getenv("PWD", data->envp);
	if (!pwd)
	{
		free_all_data(&data);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free_all_data(&data);
	exit(EXIT_SUCCESS);
}