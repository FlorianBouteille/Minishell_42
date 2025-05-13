/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:50:49 by csolari           #+#    #+#             */
/*   Updated: 2025/05/13 12:37:42 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_a_variable(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || isdigit(str[0]))
		return (ft_putstr_fd("export : not a valid identifier\n", 2), -1);
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (ft_putstr_fd("export : not a valid identifier\n", 2), -1);
		i++;
	}
	if (!contains_equal(str))
		return (0);
	return (1);
}

void	update_env(t_data **data, char *str)
{
	int	i;

	i = 0;
	while ((*data)->envp && (*data)->envp[i])
	{
		if (ft_strncmp((*data)->envp[i], str, contains_equal(str) + 1) == 0)
		{
			free((*data)->envp[i]);
			(*data)->envp[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
	add_to_env(data, str);
}

void	ft_export_parent(char **cmd, t_data **data)
{
	int	i;
	int	is_variable;

	i = 1;
	while (cmd[i])
	{
		is_variable = is_a_variable(cmd[i]);
		if (is_variable == 1)
			update_env(data, cmd[i]);
		else if (is_variable == -1)
			(*data)->exit_status = 1;
		i++;
	}
	return ;
}

void	ft_export_child(char **cmd, t_data **data)
{
	if (cmd[1] == NULL)
		print_export((*data)->envp);
	ft_free_tab((*data)->envp);
	free_all_data(data);
	exit(EXIT_SUCCESS);
}
