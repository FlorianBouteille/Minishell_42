/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:30 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 12:43:35 by csolari          ###   ########.fr       */
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

int	check_line_bis(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (line[i] < '\b' || line[i] > '\r'))
			return (1);
		i++;
	}
	g_last_signal = 0;
	return (0);
}

int	check_line(char *line)
{
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strlen(line) == 1)
	{
		if (line[0] == ':' || line[0] == '#')
		{
			g_last_signal = 0;
			return (0);
		}
		if (line[0] == '!')
		{
			g_last_signal = 1;
			return (0);
		}
	}
	return (1);
}

int	check_tokens(t_token *tokens, t_data **data)
{
	int		temp;

	temp = g_last_signal;
	g_last_signal = 2;
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
	g_last_signal = temp;
	return (1);
}
