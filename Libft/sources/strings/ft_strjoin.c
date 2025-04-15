/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:28:14 by csolari           #+#    #+#             */
/*   Updated: 2024/11/19 10:28:16 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strj;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strj = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!strj)
		return (NULL);
	ft_strlcpy(strj, s1, len1 + 1);
	ft_strlcpy((strj + len1), s2, len2 + 1);
	strj[len1 + len2] = 0;
	return (strj);
}
