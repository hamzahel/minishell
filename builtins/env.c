/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:02:04 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:31:08 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(char **av)
{
	t_env	*p;

	av++;
	if (*av)
	{
		_error("env", "bad arguments", 1);
		return ;
	}
	p = g_glob.venv;
	while (p)
	{
		if (p->value)
		{
			ft_putstr_fd(p->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(p->value, 1);
			ft_putchar_fd('\n', 1);
		}
		p = p->next;
	}
	set_status(0);
}
