/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:18:38 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:21:54 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ps_lstsize(t_pslist *stack)
{
	int			count;
	t_pslist	*lst;

	lst = stack;
	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
