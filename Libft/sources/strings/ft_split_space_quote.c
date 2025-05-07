/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:33:19 by csolari           #+#    #+#             */
/*   Updated: 2025/05/07 14:30:47 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_len(char *str)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote_type == 0)
			quote_type = str[i];
		else if (str[i] == quote_type)
			quote_type = 0;
		else if (str[i] == ' ' && quote_type == 0)
			break ;
		i++;
	}
	return (i);
}

static char	*build_word(char *str)
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

static int	count_words(char *str)
{
	int	count;
	int	len;
	int	i;

	len = 1;
	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		len = get_word_len(str + i);
		i += len;
		count++;
	}
	return (count);
}

char	**ft_split_space_quote(char *str)
{
	int		i;
	int		j;
	char	**tab;
	int		len;

	if (!str)
		return (NULL);
	tab = (char **)malloc((count_words(str) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		len = get_word_len(str + i);
		tab[j] = build_word(str + i);
		if (!tab[j])
			return (NULL);
		j++;
		i += len;
	}
	tab[j] = NULL;
	return (tab);
}
