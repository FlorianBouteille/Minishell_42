// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expand2.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/25 17:31:15 by csolari           #+#    #+#             */
// /*   Updated: 2025/04/29 13:34:14 by csolari          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int	is_variable_env(char *str)
// {
// 	if (!str || !str[1])
// 		return (-1);
// 	if (ft_isalnum(str[1]) || str[1] == '_' || str[1] == '?' || str[1] == '$')
// 		return (1);
// 	return (0);
// }

// int	count_number_variable(char *str)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	if (!str || !str[0]) 
// 		return (-1);
// 	if (str[0] == '\'' || str[ft_strlen(str) - 1] == '\'')
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && is_variable_env(str + i))
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// char	*variable_name(char *str)
// {
// 	char	*name;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	len = 0;
// 	name = NULL;
// 	if (!str)
// 		return (NULL);
// 	if (ft_isdigit(str[0]))
// 		len = 1;
// 	else
// 	{
// 		while (ft_isalnum(str[len]) || str[len] == '_')
// 			len++;
// 	}
// 	name = malloc(sizeof(char) * (len + 1));
// 	if (!name)
// 		return (ft_putstr_fd("Error : Malloc\n", 2), NULL);
// 	while (i < len)
// 	{
// 		name[i] = str[i];
// 		i++;
// 	}
// 	name[i] = 0;
// 	return (name);
// }
