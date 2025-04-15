/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:02:46 by csolari           #+#    #+#             */
/*   Updated: 2024/11/20 14:02:47 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len_s;
	size_t	i;
	char	*sf;

	i = 0;
	len_s = ft_strlen(s);
	sf = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!sf)
		return (NULL);
	while (i < len_s)
	{
		sf[i] = (*f)(i, s[i]);
		i++;
	}
	sf[i] = 0;
	return (sf);
}
