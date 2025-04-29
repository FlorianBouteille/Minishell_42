/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:42:05 by fbouteil          #+#    #+#             */
/*   Updated: 2025/04/29 12:10:37 by csolari          ###   ########.fr       */
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

char	*try_with_bin(char *str)
{
	char	*path_to_try;

	path_to_try = ft_strjoin("/bin/", str);
	if (access(path_to_try, F_OK) == 0 && access(path_to_try, X_OK) == 0)
		return (path_to_try);
	free(path_to_try);
	return (NULL);
}

char	*get_path(char *str, char *envp[])
{
	char	*path;

	if (!str)
		return (NULL);
	path = NULL;
	/*if (is_builtin(str))
		exec_builtin(str);*/
	if (access(str, X_OK) == 0)
		return (ft_strdup(str));
	if (envp)
		path = try_env_paths(str, envp);
	if (!path)
		path = try_with_bin(str);
	return (path);
}
