/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:52:19 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/05 17:02:46 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_tab(char **tab)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	if (!tab || !(*tab))
		return (NULL);
	while (tab[len])
		len++;
	copy = (char **)malloc((len + 1) * sizeof(char *));
	if (!copy)
		return (ft_putstr_fd("Error : Malloc\n", 2), NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(tab[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	get_word_len(char *str)
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

void	init_tab(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
}
