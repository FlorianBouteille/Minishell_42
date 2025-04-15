/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_firstsup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:50 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:23:09 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_firstsup(t_pslist **stack, int value)
{
	int			sup;
	t_pslist	*temp;

	sup = ft_ps_lstmax(stack);
	temp = *stack;
	while (temp)
	{
		if (temp->value > value && temp->value < sup)
			sup = temp->value;
		temp = temp->next;
	}
	return (sup);
}
