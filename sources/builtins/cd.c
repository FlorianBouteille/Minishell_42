/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:14:03 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 16:08:30 by csolari          ###   ########.fr       */
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

void	ft_cd(char **cmd, t_data **data)
{
	char	*target_path;

	target_path = NULL;
	if (!(*data)->envp)
		return ;
	if (cmd[0] && cmd[1] && cmd[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		return ;
	}
	replace_env_pwd(data, "OLDPWD=");
	if (!cmd[1])
		target_path = ft_getenv("HOME", (*data)->envp);
	else if (cmd[1][0] == '~' && ft_strlen(cmd[1]) == 1)
		target_path = ft_getenv("HOME", (*data)->envp);
	else
		target_path = cmd[1];
	if (chdir(target_path) == -1)
	{
		perror("error chdir");
		return ;
	}
	replace_env_pwd(data, "PWD=");
}
