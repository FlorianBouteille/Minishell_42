/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:56:58 by csolari           #+#    #+#             */
/*   Updated: 2024/11/15 15:57:00 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	sl;
	size_t	i;

	sl = ft_strlen(little);
	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	while (i < len && big[i] != 0)
	{
		if (big[i] == little[0] && (i + sl) <= len)
		{
			if (ft_strncmp((big + i), little, sl) == 0)
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
