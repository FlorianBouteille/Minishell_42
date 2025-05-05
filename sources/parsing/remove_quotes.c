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
	new = NULL;
	quote_type = 0;
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
	free(str);
	return (new);
}
