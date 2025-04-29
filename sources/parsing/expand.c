/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:13:22 by csolari           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/24 19:03:09 by csolari          ###   ########.fr       */
=======
/*   Updated: 2025/04/29 13:35:10 by csolari          ###   ########.fr       */
>>>>>>> 7f9c87e (export et envp)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable_env(char *str)
{
<<<<<<< HEAD
	if (!str || !str[1])
		return (-1);
	if (ft_isalnum(str[1]) || str[1] == '_')
		return (1);
	return (0);
}

int	count_number_variable(char *str)
=======
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	while (content && content[j] && str[i] == '$')
	{
		new[i + j] = content[j];
		j++;
	}
	k = len_name + 1 + i;
	while (str && str[k])
	{
		new[i + j] = str[k];
		i++;
		k++;
	}
	new[i + j] = 0;
	return (free(str), new);
}

char	*expand_dollar(char *str, int index, char **envp)
>>>>>>> 7f9c87e (export et envp)
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
<<<<<<< HEAD
	return (count);
}


void	expand_dollar(char *str, int i)
{


=======
	else if (str[index + 1] == '$')
	{
		name = ft_strdup("$");
		content = ft_getenv("SYSTEMD_EXEC_PID", envp);
	}
	else
	{
		name = variable_name(str + index + 1);
		content = ft_getenv(name, envp);
		printf("variable = %s\n", content);
	}
	len_content = ft_strlen(content);
	new = malloc(sizeof(char) * (len_content + ft_strlen(str) - ft_strlen(name)
				+ 1));
	if (!new)
		return (ft_putstr_fd("Error : malloc\n", 2), NULL);
	new = replace_content(str, content, new, ft_strlen(name));
	if (to_free)
		free(content);
	return (free(name), new);
>>>>>>> 7f9c87e (export et envp)
}

char	*check_and_replace(char *str, char **envp)
{
	int	i;
<<<<<<< HEAD
	int	is_double_quoted;

	is_double_quoted = 0;
	if (!str)
		return (NULL);
	if (str[0] == '\"')
		is_double_quoted = 1;
=======

	if (!str)
		return (NULL);
>>>>>>> 7f9c87e (export et envp)
	while (count_number_variable(str) > 0)
	{
		i = 0;
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '$')
			{
<<<<<<< HEAD
				expand_dollar(str, i);
				break;
=======
				str = expand_dollar(str, i, envp);
				break ;
>>>>>>> 7f9c87e (export et envp)
			}
			i++;
		}
	}
<<<<<<< HEAD
=======
	return (str);
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		len_str;
	int		i;

	new = NULL;
	i = 0;
	len_str = ft_strlen(str);
	if ((str[0] == '\"' && str[len_str - 1] == '\"') || (str[0] == '\''
			&& str[len_str - 1] == '\''))
	{
		new = malloc(sizeof(char) * (len_str - 1));
		if (!new)
			return (ft_putstr_fd("Error : Malloc\n", 2), NULL);
		while (i < len_str - 2)
		{
			new[i] = str[i + 1];
			i++;
		}
		new[i] = 0;
		free(str);
		return (new);
	}
	else
		return (str);
>>>>>>> 7f9c87e (export et envp)
}

void	expand_variables(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
<<<<<<< HEAD
			temp->value = check_and_replace(temp->value);
=======
			temp->value = check_and_replace(temp->value, data->envp);
			// temp->value = remove_quotes(temp->value);
			printf("token value %s\n", temp->value);
>>>>>>> 7f9c87e (export et envp)
		}
	}
}
