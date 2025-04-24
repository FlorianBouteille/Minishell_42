/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:13:22 by csolari           #+#    #+#             */
/*   Updated: 2025/04/24 19:03:09 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable_env(char *str)
{
	if (!str || !str[1])
		return (-1);
	if (ft_isalnum(str[1]) || str[1] == '_')
		return (1);
	return (0);
}

int	count_number_variable(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && is_variable_env(str + i))
			count++;
		i++;
	}
	return (count);
}


void	expand_dollar(char *str, int i)
{


}


char	*check_and_replace(char *str)
{
	int	i;
	int	is_double_quoted;

	is_double_quoted = 0;
	if (!str)
		return (NULL);
	if (str[0] == '\"')
		is_double_quoted = 1;
	while (count_number_variable(str) > 0)
	{
		i = 0;
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '$')
			{
				expand_dollar(str, i);
				break;
			}
			i++;
		}
	}
}

void	expand_variables(t_token *tokens)
{
	t_token *temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
			temp->value = check_and_replace(temp->value);
		}
	}
}
