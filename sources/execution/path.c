/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:42:05 by fbouteil          #+#    #+#             */
/*   Updated: 2025/05/06 11:33:40 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path(char *path, char *str)
{
	char	*final_path;

	final_path = ft_strjoin(path, "/");
	final_path = ft_strjoin_free(final_path, str);
	return (final_path);
}

int	contains_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*try_env_paths(char *str, char **envp)
{
	char	**env_paths_tab;
	char	*env_path_str;
	char	*path;
	int		i;

	i = 0;
	env_path_str = ft_getenv("PATH", envp);
	if (!env_path_str)
		return (NULL);
	env_paths_tab = ft_split(env_path_str, ':');
	if (!env_paths_tab)
		return (NULL);
	while (env_paths_tab[i])
	{
		path = concat_path(env_paths_tab[i], str);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	ft_free_tab(env_paths_tab);
	return (path);
}

char	*get_path(char *str, char *envp[])
{
	char	*path;

	if (!str)
		return (NULL);
	path = NULL;
	if (contains_slash(str) && access(str, X_OK) == 0)
		return (str);
	if (envp && !contains_slash(str))
		path = try_env_paths(str, envp);
	return (path);
}
