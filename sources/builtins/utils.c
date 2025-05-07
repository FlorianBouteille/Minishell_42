/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:01:58 by csolari           #+#    #+#             */
/*   Updated: 2025/05/06 12:06:03 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_parent(char **cmd, t_data *data)
{
	int	len_cmd;

	if (!cmd || !cmd[0])
		return (-1);
	len_cmd = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0], "export", len_cmd) == 0 && len_cmd == 6)
		return (ft_export_parent(cmd, &data), 1);
	else if (ft_strncmp(cmd[0], "cd", len_cmd) == 0 && len_cmd == 2)
		return (ft_cd(cmd, &data), 1);
	else if (ft_strncmp(cmd[0], "unset", len_cmd) == 0 && len_cmd == 5)
		return (ft_unset(cmd, &data), 1);
	else if (ft_strncmp(cmd[0], "exit", len_cmd) == 0 && len_cmd == 4)
		return (ft_exit(cmd, data), 1);
	return (0);
}

int	is_builtin_child(char **cmd, t_data *data)
{
	int	len_cmd;

	if (!cmd || !cmd[0])
		return (-1);
	len_cmd = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0], "export", len_cmd) == 0 && len_cmd == 6)
		return (ft_export_child(cmd, &data), 1);
	else if (ft_strncmp(cmd[0], "echo", len_cmd) == 0 && len_cmd == 4)
		return (ft_echo(cmd, data), 1);
	else if (ft_strncmp(cmd[0], "pwd", len_cmd) == 0 && len_cmd == 3)
		return (ft_pwd(data), 1);
	else if (ft_strncmp(cmd[0], "env", len_cmd) == 0 && len_cmd == 3)
		return (ft_env(data), 1);
	return (0);
}
