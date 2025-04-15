/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_firstinf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:46:56 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:23:22 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_firstinf(t_pslist **stack, int value)
{
	int			inf;
	t_pslist	*temp;

	inf = ft_ps_lstmin(stack);
	temp = *stack;
	while (temp)
	{
		if (temp->value < value && temp->value > inf)
			inf = temp->value;
		temp = temp->next;
	}
	return (inf);
}
