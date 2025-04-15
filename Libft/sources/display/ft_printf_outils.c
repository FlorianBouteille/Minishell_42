/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:10:02 by csolari           #+#    #+#             */
/*   Updated: 2025/02/04 15:47:44 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_putchar_fd(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_putstr_void_fd(void *s)
{
	int	len_s;

	if (s == NULL)
	{
		len_s = ft_print_putstr_fd("(null)");
		return (len_s);
	}
	len_s = ft_strlen((char *)s);
	ft_putstr_fd((char *)s, 1);
	return (len_s);
}

int	ft_print_putnbr_fd(int nbr)
{
	int		len;
	char	*n;

	n = ft_itoa(nbr);
	ft_putstr_fd(n, 1);
	len = ft_strlen(n);
	free(n);
	return (len);
}

int	ft_print_uns_dec(unsigned int nbr)
{
	int		len;
	char	*n;

	n = ft_uitoa(nbr);
	ft_putstr_fd(n, 1);
	len = ft_strlen(n);
	free(n);
	return (len);
}
