/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:39:33 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:22:56 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ps_index(t_pslist **stack, int value)
{
	int			i;
	t_pslist	*temp;

	i = 0;
	temp = *stack;
	while (temp)
	{
		if (value == temp->value)
			return (i);
		i++;
		temp = temp->next;
	}
	return (-1);
}
