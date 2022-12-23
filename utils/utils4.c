/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:18:22 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:30:26 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_glob.is_runing)
		return ;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_status(1);
}

void	sig_init(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		_error("signal", strerror(errno), 1);
}

void	sig_restore(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
		signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		_error("signal", strerror(errno), 1);
}
