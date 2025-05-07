/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:21:53 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/07 14:19:34 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_expanded_str(char *new, char *str, char *content, char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < contains_expandables(str))
	{
		new[i] = str[i];
		i++;
	}
	j = 0;
	while (content && content[j])
	{
		new[i + j] = content[j];
		j++;
	}
	j += i;
	i += ft_strlen(name);
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

char	*build_new_token(char *str, char *name, char *content)
{
	char	*new;
	int		len_to_remove;
	int		len_to_add;

	len_to_remove = ft_strlen(name);
	len_to_add = ft_strlen(content);
	new = (char *)malloc((ft_strlen(str) - len_to_remove + len_to_add + 2)
			* sizeof(char));
	if (!new)
		return (NULL);
	new = fill_expanded_str(new, str, content, name);
	free(str);
	free(content);
	free(name);
	return (new);
}

char	*get_content(char *str, char **envp)
{
	if (!str)
		return (NULL);
	if (str[0] == '?')
		return (ft_itoa(g_last_signal));
	else if (str[0] == '$')
		return (ft_strdup(ft_getenv("SYSTEMD_EXEC_PID", envp)));
	else
		return (ft_strdup(ft_getenv(str, envp)));
	return (NULL);
}

char	*replace_first_expandable(char *str, char **envp)
{
	int		i;
	char	*name;
	char	*content;
	char	*new;

	i = 0;
	name = var_to_replace(str + contains_expandables(str));
	content = get_content(name + 1, envp);
	new = build_new_token(str, name, content);
	return (new);
}
