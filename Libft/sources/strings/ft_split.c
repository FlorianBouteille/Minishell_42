/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:27:44 by csolari           #+#    #+#             */
/*   Updated: 2025/04/18 12:10:08 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, char sep)
{
	size_t	count;
	size_t	is_sep;
	size_t	i;

	count = 0;
	is_sep = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != sep && is_sep == 1)
		{
			count += 1;
			is_sep = 0;
		}
		if (s[i] == sep)
			is_sep = 1;
		i++;
	}
	return (count);
}

static size_t	ft_find_word(const char *s, char sep, size_t index)
{
	size_t	count;
	size_t	is_sep;
	size_t	i;

	count = 0;
	is_sep = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != sep && is_sep == 1)
		{
			count += 1;
			is_sep = 0;
		}
		if (s[i] == sep)
			is_sep = 1;
		if (count == index + 1)
			return (i);
		i++;
	}
	return (i);
}

static size_t	ft_end_word(const char *s, char sep, size_t index)
{
	size_t	count;
	size_t	is_sep;
	size_t	i;

	count = 0;
	is_sep = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == sep && is_sep == 0)
		{
			is_sep = 1;
			count += 1;
		}
		if (s[i] != sep)
			is_sep = 0;
		if (count == index + 1)
			return (i);
		i++;
	}
	return (i);
}

static void	ft_free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**tab;
	size_t	i;
	size_t	start;
	size_t	len;

	if (!s)
		return (NULL);
	count = ft_count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < count)
	{
		start = ft_find_word(s, c, i);
		len = ft_end_word(s, c, i) - start;
		tab[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!tab[i])
			return (ft_free_tab(tab, (int)i - 1), NULL);
		ft_strlcpy(tab[i], (s + start), len + 1);
		i++;
	}
	tab[count] = NULL;
	return (tab);
}
