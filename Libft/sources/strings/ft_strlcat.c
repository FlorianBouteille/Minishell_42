/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:40:03 by csolari           #+#    #+#             */
/*   Updated: 2024/11/13 14:40:05 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	ts;
	size_t	td;
	size_t	k;

	ts = ft_strlen(src);
	td = ft_strlen((const char *)dst);
	if (!siz)
		return (ts);
	if (td > siz)
		return (ts + siz);
	k = 0;
	while (src[k] != 0 && (td + k) < (siz - 1))
	{
		dst[td + k] = src[k];
		k++;
	}
	dst[td + k] = 0;
	return (td + ts);
}
