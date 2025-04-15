/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:24:44 by csolari           #+#    #+#             */
/*   Updated: 2024/11/15 12:24:46 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*last_find;

	i = 0;
	last_find = NULL;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			last_find = (char *)(s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		last_find = (char *)(s + i);
	return (last_find);
}
