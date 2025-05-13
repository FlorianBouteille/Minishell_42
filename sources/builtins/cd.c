/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:14:03 by csolari           #+#    #+#             */
/*   Updated: 2025/05/13 14:46:06 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_pwd(t_data **data, char *variable)
{
	int		i;
	char	*actual_path;
	char	*variable_name_content;

	i = 0;
	actual_path = NULL;
	variable_name_content = NULL;
	actual_path = getcwd(NULL, 0);
	variable_name_content = ft_strjoin_free2(ft_strdup(variable), actual_path);
	while ((*data)->envp[i])
	{
		if (ft_strncmp((*data)->envp[i], variable, ft_strlen(variable)) == 0)
		{
			free((*data)->envp[i]);
			(*data)->envp[i] = variable_name_content;
			return ;
		}
		i++;
	}
	free(variable_name_content);
}

char	*get_target_path(char *cmd, char **envp)
{
	char	*target_path;
	char	*pwd;

	if (!cmd)
		target_path = ft_getenv("HOME", envp);
	else if (cmd && cmd[0] == '~' && ft_strlen(cmd) == 1)
		target_path = ft_getenv("HOME", envp);
	else if (cmd && cmd[0] == '-' && ft_strlen(cmd) == 1)
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		free(pwd);
		return (NULL);
	}
	else
		target_path = cmd;
	return (target_path);
}

void	ft_cd(char **cmd, t_data **data)
{
	char	*target_path;

	if (!(*data)->envp)
		return ;
	if (cmd[0] && cmd[1] && cmd[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		(*data)->exit_status = 1;
		return ;
	}
	replace_env_pwd(data, "OLDPWD=");
	target_path = get_target_path(cmd[1], (*data)->envp);
	if (cmd[1] && cmd[1][0] == '-' && ft_strlen(cmd[1]) == 1)
		return ;
	if (chdir(target_path) == -1)
	{
		perror("error chdir");
		(*data)->exit_status = 1;
		return ;
	}
	replace_env_pwd(data, "PWD=");
}
