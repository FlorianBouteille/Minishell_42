/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:13:22 by csolari           #+#    #+#             */
/*   Updated: 2025/04/25 13:20:25 by csolari          ###   ########.fr       */
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

char	*variable_name(char *str)
{
	char	*name;
	int		len;
	int		i;

	i = 0;
	len = 0;
	name = NULL;
	if (!str)
		return (NULL);
	if (ft_isdigit(str[0]))
		len = 1;
	else
	{
		while (ft_isalnum(str[len]) || str[len] == '_')
			len++;
	}
	name = malloc(sizeof(char)* (len + 1));
	if (!name)
		return (ft_putstr_fd("Error : Malloc\n", 2), NULL);
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

// calculer longueur du contenu a inserrer
// longueur string de base moins non variable
//malloc niuvelle string
// copier les infos en remplacant au bon endroit
// free l ancienne str
// remplacer pointeur sur str vers la nouvelle
char	*expand_dollar(char *str, int index)
{
	char	*content;
	char	*name;
	char	*new;
	int		len_content;
	int		i;
	int		j;
	int		content_copied;

	printf("str = %s\n", str + index);
	content_copied = 0;
	name = variable_name(str + index + 1);
	printf("name = %s\n", name);
	content = getenv(name);
	printf("content = %s\n", content);
	len_content = ft_strlen(content);
	new = malloc(sizeof(char) * (len_content + ft_strlen(str) - ft_strlen(name) + 1));
	if (!new)
		return (ft_putstr_fd("Error : malloc\n", 2), NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			while (j < len_content)
			{
				new[i + j] = content[j];
				j++;
			}
			i += (ft_strlen(name) + 1);
		}
		else
		{
			new[i + j] = str[i];
			i++;
		}
	}
	new[i + j] = 0;

	free(str);
	printf("new = %s\n", new);
	return(new);
}


char	*check_and_replace(char *str)
{
	int	i;
	int	is_double_quoted;
	int	condition;

	is_double_quoted = 0;
	if (!str)
		return(NULL);
	if (str[0] == '\"')
		is_double_quoted = 1;
	condition = 1;
	while (condition > 0)
	{
		i = 0;
		printf("number variable start : %i\n", count_number_variable(str));
		while (str[i] && str)
		{
			if (str[i] == '$')
			{
				str = expand_dollar(str, i);
				printf("new = %s\n", str);
				break;
			}
			i++;
		}
		condition = count_number_variable(str);
		printf("number variable end : %i\n", count_number_variable(str));
		break ;
	}
	return (str);
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
			printf("token value %s\n", temp->value);
		}
		temp = temp->next;
	}
}
