/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:45:06 by csolari           #+#    #+#             */
/*   Updated: 2024/11/26 15:45:08 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*flst;
	t_list	*newelem;

	if (!lst || !f || !del)
		return (NULL);
	flst = NULL;
	newelem = NULL;
	while (lst)
	{
		newelem = ft_lstnew(f(lst->content));
		if (!newelem)
		{
			ft_lstclear(&flst, del);
			return (NULL);
		}
		ft_lstadd_back(&flst, newelem);
		lst = lst->next;
	}
	return (flst);
}
