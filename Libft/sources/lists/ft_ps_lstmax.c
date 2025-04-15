/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_lstmax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:36:56 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:22:02 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ps_lstmax(t_pslist **stack)
{
	t_pslist	*temp;
	int			max;

	max = -2147483648;
	temp = *stack;
	while (temp)
	{
		if (max < temp->value)
			max = temp->value;
		temp = temp->next;
	}
	return (max);
}
