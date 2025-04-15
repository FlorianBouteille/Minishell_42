/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:22:59 by csolari           #+#    #+#             */
/*   Updated: 2024/11/19 14:23:00 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 0;
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static void	ft_putinstr(int i, char *str, long nbr, int sign)
{
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i--;
	}
	if (sign == 1)
		str[0] = 45;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;
	long	nbr;

	nbr = n;
	i = 0;
	sign = 0;
	if (nbr < 0)
	{
		sign = 1;
		nbr = -nbr;
		i += 1;
	}
	i += ft_count(nbr);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_putinstr(i, str, nbr, sign);
	return (str);
}
