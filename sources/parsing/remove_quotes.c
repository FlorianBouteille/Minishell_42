/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:55:59 by csolari           #+#    #+#             */
/*   Updated: 2025/05/07 14:31:45 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_len(char *str)
{
	int	i;
	int	count;
	int	quote_type;

	i = 0;
	count = 0;
	quote_type = 0;
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote_type == 0)
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = 0;
		else
			count++;
		i++;
	}
	if (quote_type)
		return (-1);
	return (count);
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		quote_type;

	i = 0;
	j = 0;
	quote_type = 0;
	if (get_new_len(str) == -1)
		return (str);
	new = (char *)malloc((get_new_len(str) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote_type == 0)
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = 0;
	return (free(str), new);
}

void	remove_quotes_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		tab[i] = remove_quotes(tab[i]);
		i++;
	}
}
