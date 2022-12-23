/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:22:41 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 22:56:21 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status(int status)
{
	g_glob.status = status * 256;
}

int	get_status(void)
{
	if (WIFSIGNALED(g_glob.status))
		return (128 + WTERMSIG(g_glob.status));
	else if (WIFSTOPPED(g_glob.status))
		return (128 + WSTOPSIG(g_glob.status));
	else if (WIFEXITED(g_glob.status))
		return (WEXITSTATUS(g_glob.status));
	return (1);
}

void	_error(char *title, char *msg, int status)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(title, STDERR_FILENO);
	if (msg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	set_status(status);
}

void	_error_exit(char *title, char *msg, int status)
{
	_error(title, msg, status);
	gc_clean(&g_glob.gc, GC_DESTROY_SELF);
	rl_clear_history();
	exit(status);
}
