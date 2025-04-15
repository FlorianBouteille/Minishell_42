/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_printlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:44:43 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:21:15 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_pslist **lst, char c)
{
	t_pslist	*temp;

	temp = *lst;
	ft_printf("Stack %c\n-------\n", c);
	while (temp)
	{
		ft_printf("%i\n", temp->value);
		temp = temp->next;
	}
	ft_printf("-------\n\n");
}
