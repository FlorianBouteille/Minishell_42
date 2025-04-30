/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:01:58 by csolari           #+#    #+#             */
/*   Updated: 2025/04/30 14:24:16 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_parent(char **cmd, t_data *data)
{
	int		len_cmd;

	if (!cmd || !cmd[0])
		return (-1);
	len_cmd = ft_strlen(cmd[0]);
	printf("cmd[0] = %s\n", cmd[0]);
	if (ft_strncmp(cmd[0], "export", len_cmd) == 0 && len_cmd == 6)
		ft_export_parent(cmd, &data);
	else if (ft_strncmp(cmd[0], "cd", len_cmd) == 0 && len_cmd == 2)
		ft_cd(cmd, data);
	else if (ft_strncmp(cmd[0], "unset", len_cmd) == 0 && len_cmd == 5)
		ft_unset(cmd, &data);
	// else if (ft_strncmp(cmd[0], "exit", len_cmd) == 0 && len_cmd == 4)
	// 	ft_exit(cmd, data);
	return (0);
}

int	is_builtin_child(char **cmd, t_data *data)
{
	int		len_cmd;

	if (!cmd || !cmd[0])
		return (-1);
	len_cmd = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0], "export", len_cmd) == 0 && len_cmd == 6)
		return(ft_export_child(cmd, &data), 1);
	// else if (ft_strncmp(cmd[0], "echo", len_cmd) == 0 && len_cmd == 4)
	// 	ft_echo(cmd, data);
	else if (ft_strncmp(cmd[0], "pwd", len_cmd) == 0 && len_cmd == 3)
		ft_pwd(data);
	else if (ft_strncmp(cmd[0], "env", len_cmd) == 0 && len_cmd == 3)
		return(ft_env(data), 1);
	// else if (ft_strncmp(cmd[0], "exit", len_cmd) == 0 && len_cmd == 4)
	// 	ft_exit(cmd, data);
	return (0);
}