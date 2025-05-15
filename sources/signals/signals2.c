/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:46:16 by csolari           #+#    #+#             */
/*   Updated: 2025/05/15 12:00:38 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (!g_last_signal && signum == SIGINT)
		g_last_signal = 130;
	if (signum == SIGINT || signum == SIGCHLD)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_child(int signum)
{
	(void)signum;
	g_last_signal = 130;
	write(2, "\n", 1);
	exit(130);
}

void	sigint_heredoc(int signum)
{
	(void)signum;
	g_last_signal = 130;
	write(2, "\n", 1);
	close(0);
}
