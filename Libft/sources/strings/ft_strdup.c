/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:12:36 by csolari           #+#    #+#             */
/*   Updated: 2025/05/02 12:41:04 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		count;

	if (!s)
		return (NULL);
	count = ft_strlen(s);
	cpy = (char *)malloc(sizeof(char) * (count + 1));
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, s, (count + 1));
	return (cpy);
}
