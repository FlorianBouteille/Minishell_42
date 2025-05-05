/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:56:37 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/05 17:03:46 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_type(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '>')
			return (TOKEN_REDIR_OUT);
		else if (str[0] == '<')
			return (TOKEN_REDIR_IN);
		else if (str[0] == '|')
			return (TOKEN_PIPE);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '>' && str[1] == '>')
			return (TOKEN_APPEND);
		else if (str[0] == '<' && str[1] == '<')
			return (TOKEN_HEREDOC);
	}
	return (TOKEN_WORD);
}

t_token	*new_token(char *str)
{
	t_token	*token;

	token = NULL;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = make_word(str);
	token->type = find_type(token->value);
	token->next = NULL;
	return (token);
}

void	add_token(char *str, t_token **tokens)
{
	t_token	*tmp;

	if (!(*tokens))
		*tokens = new_token(str);
	else
	{
		tmp = *tokens;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_token(str);
	}
}

t_token	*lex_string(char *str)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ')
			add_token((str + i), &tokens);
		i += get_word_len(str + i);
	}
	free(str);
	return (tokens);
}
