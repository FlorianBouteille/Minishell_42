/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_sep.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:27:04 by csolari           #+#    #+#             */
/*   Updated: 2025/05/13 10:26:48 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_joined_str(char *strj, char *s1, char *s2, char c)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		strj[i] = s1[i];
		i++;
	}
	strj[i++] = c;
	while (s2 && s2[j])
	{
		strj[i + j] = s2[j];
		j++;
	}
	strj[ft_strlen(s1) + ft_strlen(s2) + 1] = 0;
}

char	*ft_strjoin_free_sep(char *s1, char *s2, char c)
{
	char	*strj;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (NULL);
	strj = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!strj)
		return (free(s1), NULL);
	fill_joined_str(strj, s1, s2, c);
	return (free(s1), strj);
}
