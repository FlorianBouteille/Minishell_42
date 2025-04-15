/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:43:57 by csolari           #+#    #+#             */
/*   Updated: 2025/02/04 15:46:18 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_type(char c, va_list list)
{
	int		print_len;
	char	*b_min;
	char	*b_maj;

	b_min = "0123456789abcdef";
	b_maj = "0123456789ABCDEF";
	print_len = 0;
	if (c == 'c')
		print_len = ft_print_putchar_fd(va_arg(list, int));
	if (c == 's')
		print_len = ft_print_putstr_void_fd(va_arg(list, void *));
	if (c == 'p')
		print_len = ft_print_putptr(va_arg(list, unsigned long int));
	if (c == 'd' || c == 'i')
		print_len = ft_print_putnbr_fd(va_arg(list, int));
	if (c == 'u')
		print_len = ft_print_uns_dec(va_arg(list, unsigned int));
	if (c == 'x')
		print_len = ft_print_hex(va_arg(list, unsigned int), b_min);
	if (c == 'X')
		print_len = ft_print_hex(va_arg(list, unsigned int), b_maj);
	if (c == '%')
		print_len = ft_print_putchar_fd('%');
	return (print_len);
}

int	ft_printf(const char *arg0, ...)
{
	va_list	list;
	int		print_len;
	size_t	i;

	i = 0;
	print_len = 0;
	if (!arg0)
		return (-1);
	va_start(list, arg0);
	while (arg0[i])
	{
		if (arg0[i] == '%' && arg0[i + 1] != '\0')
		{
			print_len += ft_print_type(arg0[i + 1], list);
			i++;
		}
		else
			print_len += ft_print_putchar_fd(arg0[i]);
		i++;
	}
	va_end(list);
	return (print_len);
}

// int	main()
// {
// 	// i = ft_printf("%u, et oui 100%% hep\n", 654);
// 	ft_printf(" NULL %x NULL ", 255);
//	printf("\n");
// 	printf(" NULL %x NULL ", 255);
// 	return(1);
// }