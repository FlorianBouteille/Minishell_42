/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:24:17 by csolari           #+#    #+#             */
/*   Updated: 2025/05/05 12:46:43 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free2(char *s1, char *s2)
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
		return (free(s1), free(s2), NULL);
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
	return (free(s1), free(s2), strj);
}
