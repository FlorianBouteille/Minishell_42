/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:30 by csolari           #+#    #+#             */
/*   Updated: 2025/04/29 10:40:32 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_meta_caracters(char *str)
{
	if (str[0] == '<' || str[0] == '>')
	{
		if (ft_strlen(str) == 1 || ft_strlen(str) == 2)
			return (1);
		return (0);
	}
	if (str[0] == '|' && ft_strlen(str) != 1)
		return (0);
	return (1);
}

int	check_tokens(t_token *tokens, t_data **data)
{
	t_token	*tmp;

	if (!tokens)
		return (lex_error(NULL, data), 0);
	tmp = tokens;
	if (tokens->type == TOKEN_PIPE)
		return (lex_error("syntax error near |", data), 0);
	while (tokens)
	{
		if (!check_meta_caracters(tokens->value))
			return (lex_error("syntax error near <, > or | !", data), 0);
		if (tokens->type != TOKEN_WORD && tokens->type != TOKEN_PIPE)
		{
			if (!(tokens->next) || tokens->next->type != TOKEN_WORD)
				return (lex_error("syntax error : file missing !", data), 0);
		}
		if (tokens->type == TOKEN_PIPE)
		{
			if (!(tokens->next) || tokens->next->type == TOKEN_PIPE)
				return (lex_error("syntax error : near |", data), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}

// CHECK SI LA COMMANDE EST VIDE OU QUE DES ESPACES