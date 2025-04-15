/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:48:50 by csolari           #+#    #+#             */
/*   Updated: 2025/02/05 13:22:21 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_base(unsigned long int n, char *base)
{
	int					i;
	char				*s;
	unsigned long int	nb;

	nb = n;
	i = 0;
	while (nb / 16 > 0)
	{
		i++;
		nb = nb / 16;
	}
	s = (char *)malloc(sizeof(char) * (i + 2));
	ft_bzero(s, i + 2);
	if (!s)
		return (NULL);
	s[i] = 0;
	while (i >= 0)
	{
		s[i] = base[n % 16];
		n = n / 16;
		i--;
	}
	return (s);
}
