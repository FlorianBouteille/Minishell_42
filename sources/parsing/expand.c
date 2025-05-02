/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:21:46 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/02 16:32:03 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		tmp->value = expand_dollars(tmp->value, data->envp);
		//tmp->value = remove_quotes(tmp->value);
		tmp = tmp->next;
	}
}

int	contains_expandables(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (-1);
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$')
		{
			if (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'
				|| str[i + 1] == '$')
				return (i);
		}
		i++;
	}
	return (-1);
}

int	len_to_replace(char *str)
{
	int	i;

	i = 0;
	if (str[1] == '$' || str[1] == '?' || ft_isdigit(str[1]))
		return (2);
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*var_to_replace(char *str)
{
	int		i;
	int		var_len;
	char	*var_name;

	i = 0;
	var_len = len_to_replace(str);
	printf("len to replace = %i\n", var_len);
	var_name = (char *)malloc((var_len + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	while (i < var_len)
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = 0;
	return (var_name);
}

char	*expand_dollars(char *str, char **envp)
{
	while (contains_expandables(str) != -1)
		str = replace_first_expandable(str, envp);
	return (str);
}
