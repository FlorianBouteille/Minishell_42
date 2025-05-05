/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:54:14 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 16:23:20 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_unset(t_data **data, char *variable, char **new_env, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (!(ft_strncmp((*data)->envp[i], variable, ft_strlen(variable)) == 0
				&& (*data)->envp[i][ft_strlen(variable)] == '='))
		{
			new_env[j] = ft_strdup((*data)->envp[i]);
			if (!new_env[j])
				return ;
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_tab((*data)->envp);
	(*data)->envp = new_env;
}

void	unset_variable(t_data **data, char *variable)
{
	char	**new_env;
	int		len;

	len = 0;
	new_env = NULL;
	if (!ft_getenv(variable, (*data)->envp))
		return ;
	else
	{
		if (!(*data)->envp || !(*data)->envp)
			return ;
		while ((*data)->envp[len])
			len++;
		new_env = (char **)malloc((len) * sizeof(char *));
		if (!new_env)
			return (ft_putstr_fd("Error : Malloc\n", 2));
		apply_unset(data, variable, new_env, len);
	}
}

void	ft_unset(char **cmd, t_data **data)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		unset_variable(data, cmd[i]);
		i++;
	}
}
