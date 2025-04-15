/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:47:25 by csolari           #+#    #+#             */
/*   Updated: 2025/02/05 13:22:06 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	char			*str;
	int				i;
	unsigned long	nbr;

	nbr = n;
	i = 0;
	while (nbr / 10 > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	nbr = n;
	i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i--;
	}
	return (str);
}
