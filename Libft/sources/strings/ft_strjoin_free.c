/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:07:01 by csolari           #+#    #+#             */
/*   Updated: 2025/03/13 14:04:20 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*strj;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (NULL);
	strj = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!strj)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		strj[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		strj[i + j] = s2[j];
		j++;
	}
	strj[ft_strlen(s1) + ft_strlen(s2)] = 0;
	return (free(s1), strj);
}
