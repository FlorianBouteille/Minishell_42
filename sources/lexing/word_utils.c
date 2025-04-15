/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:19 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/15 13:52:20 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_word_len(char *str)
{
	int	i;
	int quote_type;

	i = 0;
	quote_type = 0;
	if (str[i] == '\'' || str[i] == '\"')
		quote_type = str[i++];
	if (!quote_type)
	{
		while (str[i] && str[i] != ' ')
			i++;
	}
	else
	{
		while (str[i] && str[i] != quote_type)
			i++;
		if (str[i] && str[i] == quote_type)
			i++;
	}
	return (i);
}

char	*make_word(char *str)
{
	int		len;
	char	*word;

	len = get_word_len(str);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, (size_t)len + 1);
	return (word);
}
