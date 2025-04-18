/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:30 by csolari           #+#    #+#             */
/*   Updated: 2025/04/18 12:30:49 by csolari          ###   ########.fr       */
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

void	check_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tokens->type == TOKEN_PIPE)
	{
		lex_error("syntax error near |\n", &tmp);			
		return ;
	}
	while (tokens)
	{
		if (!check_meta_caracters(tokens->value))
			lex_error("syntax error near <, > or | !\n", &tmp);
		if (tokens->type != TOKEN_WORD && tokens->type != TOKEN_PIPE)
		{
			if (!(tokens->next) || tokens->next->type != TOKEN_WORD)
				lex_error("syntax error : file missing !\n", &tmp);
		}
		if (tokens->type == TOKEN_PIPE)
		{
			if (!(tokens->next) || tokens->next->type == TOKEN_PIPE)
				lex_error("syntax error : near |\n", &tmp);
		} 
		tokens = tokens->next;
	}
}

