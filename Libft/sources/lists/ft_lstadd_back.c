/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:12:02 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 16:19:34 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*mem;

	if (!new || !lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		mem = *lst;
		while (mem->next)
			mem = mem->next;
		mem->next = new;
	}
}
