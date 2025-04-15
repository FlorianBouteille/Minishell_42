/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:58:59 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/15 13:59:00 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	
	if (!(*tokens))
		return ;
	tmp = *tokens;
	while (tmp)
	{
		tmp = tmp->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
}
