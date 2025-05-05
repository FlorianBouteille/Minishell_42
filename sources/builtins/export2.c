/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:58:46 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 16:20:40 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(t_data **data, char *str)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	while ((*data)->envp && (*data)->envp[len])
		len++;
	copy = (char **)malloc((len + 2) * sizeof(char *));
	if (!copy)
		return (ft_putstr_fd("Error : Malloc\n", 2));
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup((*data)->envp[i]);
		if (!copy[i])
			return ;
		i++;
	}
	copy[i] = ft_strdup(str);
	if (!copy[i])
		return (ft_putstr_fd("Error : Malloc\n", 2));
	copy[++i] = NULL;
	ft_free_tab((*data)->envp);
	(*data)->envp = copy;
}

void	print_export(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	while (tab[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
