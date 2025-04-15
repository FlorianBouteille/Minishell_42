/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:03:52 by csolari           #+#    #+#             */
/*   Updated: 2024/11/19 11:03:54 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*strim;

	start = 0;
	end = ft_strlen(s1);
	if (!s1[0])
	{
		strim = (char *)malloc(sizeof(char) * 1);
		if (!strim)
			return (NULL);
		strim[0] = '\0';
		return (strim);
	}
	while (ft_strchr(set, s1[start]) && start < end)
		start++;
	while (ft_strchr(set, s1[end - 1]) && end > 0)
		end--;
	if (start > end)
		return (ft_strdup(""));
	strim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!strim)
		return (NULL);
	ft_strlcpy(strim, (s1 + start), end - start + 1);
	return (strim);
}
