/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:22:33 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:26:02 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pslist	*ft_ps_lstnew(int content)
{
	t_pslist	*new;

	new = (t_pslist *)malloc(sizeof(t_pslist));
	if (!new)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}
