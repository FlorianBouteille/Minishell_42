/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:55:59 by csolari           #+#    #+#             */
/*   Updated: 2025/05/02 15:08:08 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new;
	int		len_str;
	int		i;

	new = NULL;
	i = 0;
	len_str = ft_strlen(str);
	if ((str[0] == '\"' && str[len_str - 1] == '\"') || (str[0] == '\''
			&& str[len_str - 1] == '\''))
	{
		new = malloc(sizeof(char) * (len_str - 1));
		if (!new)
			return (ft_putstr_fd("Error : Malloc\n", 2), NULL);
		while (i < len_str - 2)
		{
			new[i] = str[i + 1];
			i++;
		}
		new[i] = 0;
		free(str);
		return (new);
	}
	else
		return (str);
}
