/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:35:58 by csolari           #+#    #+#             */
/*   Updated: 2025/05/07 13:42:11 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	return ((c == '>' || c == '<' || c == '|'));
}

char	*add_space(char *str, int index)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < index)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = ' ';
	while (str[i])
	{
		new_str[i + 1] = str[i];
		i++;
	}
	free(str);
	new_str[i + 1] = 0;
	return (new_str);
}

char	*add_spaces(char *str)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i + 1])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote_type == 0)
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = 0;
		if (!is_special(str[i]) && is_special(str[i + 1]) && str[i] != ' '
			&& quote_type == 0)
			str = add_space(str, (i + 1));
		if (is_special(str[i]) && str[i + 1] != str[i] && str[i + 1] != ' '
			&& quote_type == 0)
			str = add_space(str, (i + 1));
		i++;
	}
	return (str);
}
