/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:19:04 by csolari           #+#    #+#             */
/*   Updated: 2024/11/13 14:19:06 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t siz)
{
	unsigned int	j;	
	unsigned int	i;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	if (siz == 0)
		return (i);
	while (j < (siz -1) && src[j] != 0)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (i);
}
