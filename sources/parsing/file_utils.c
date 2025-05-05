/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:17:55 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/05 17:01:12 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*create_new_file(char *name, char *limiter, int out_append)
{
	t_file	*new;

	new = NULL;
	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->name = name;
	new->limiter = limiter;
	new->out_append = out_append;
	new->next = NULL;
	return (new);
}

void	add_file_back(t_file **files, char *name, char *limiter, int out_append)
{
	t_file	*temp;

	if (!files || !(*files))
	{
		*files = create_new_file(name, limiter, out_append);
		return ;
	}
	temp = *files;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = create_new_file(name, limiter, out_append);
}

/*
->singleton statique local
static t_data data; crée une seule instance de data, conservée entre les appels.
À chaque appel de ft_getdata(), tu récupères le même pointeur.
Ce n’est pas une variable globale (au sens fichier),
	elle est locale à la fonction,
donc pas exposée.
Tu peux appeler ft_getdata() de n’importe où,
	et tant que tu ne fais pas de free dessus
(ce qu’il ne faut surtout pas faire), ça reste en mémoire sans fuite.

t_data	*ft_getdata(void)
{
	static t_data	data;

	return (&data);
}
*/