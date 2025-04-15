/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_lstmin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:49:31 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:23:33 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ps_lstmin(t_pslist **stack)
{
	t_pslist	*temp;
	int			min;

	min = 2147483647;
	temp = *stack;
	while (temp)
	{
		if (min > temp->value)
			min = temp->value;
		temp = temp->next;
	}
	return (min);
}
